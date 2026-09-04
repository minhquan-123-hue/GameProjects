/**
 * quizContentLoader.js
 *
 * Data layer: đọc question-content.md, parse question/answers và cập nhật
 * question pool trong QUIZ_DATA. Không chứa logic UI/game state.
 */

const QUIZ_CONTENT_PATH = '../content/question-content.md';

function normalizeQuizText(value) {
    return String(value || '')
        .normalize('NFD')
        .replace(/[\u0300-\u036f]/g, '')
        .toLowerCase()
        .replace(/[\u2018\u2019\u201c\u201d`"']/g, '')
        .replace(/\s+/g, ' ')
        .trim();
}

function levenshteinDistance(a, b) {
    const rows = b.length + 1;
    const cols = a.length + 1;
    const matrix = Array.from({ length: rows }, (_, row) => {
        const values = new Array(cols);
        values[0] = row;
        return values;
    });

    for (let col = 0; col < cols; col++) matrix[0][col] = col;

    for (let row = 1; row < rows; row++) {
        for (let col = 1; col < cols; col++) {
            const cost = b[row - 1] === a[col - 1] ? 0 : 1;
            matrix[row][col] = Math.min(
                matrix[row - 1][col] + 1,
                matrix[row][col - 1] + 1,
                matrix[row - 1][col - 1] + cost
            );
        }
    }

    return matrix[rows - 1][cols - 1];
}

function findCorrectIndex(answer, options) {
    const normalizedAnswer = normalizeQuizText(answer);
    const normalizedOptions = options.map(normalizeQuizText);

    const exactIndex = normalizedOptions.indexOf(normalizedAnswer);
    if (exactIndex !== -1) return exactIndex;

    const candidates = normalizedOptions
        .map((option, index) => ({
            index,
            distance: levenshteinDistance(normalizedAnswer, option)
        }))
        .sort((a, b) => a.distance - b.distance);

    const best = candidates[0];
    const secondBest = candidates[1];
    const maxDistance = Math.max(1, Math.floor(normalizedAnswer.length * 0.18));

    if (
        best &&
        best.distance <= maxDistance &&
        (!secondBest || best.distance < secondBest.distance)
    ) {
        console.warn(
            `Quiz answer typo normalized: "${answer}" → "${options[best.index]}"`
        );
        return best.index;
    }

    throw new Error(
        `Không xác định được đáp án đúng: "${answer}". Options: ${options.join(' | ')}`
    );
}

function parseAnswerOptions(line) {
    const matches = [...line.matchAll(/(?:^|\s)([a-d])\.\s*/gi)];

    if (
        matches.length !== 4 ||
        matches.map(match => match[1].toLowerCase()).join('') !== 'abcd'
    ) {
        return null;
    }

    return matches.map((match, index) => {
        const start = match.index + match[0].length;
        const end = index < matches.length - 1
            ? matches[index + 1].index
            : line.length;
        return line.slice(start, end).trim();
    });
}

function parseQuizContent(markdown) {
    const entries = [];
    const lines = markdown.split(/\r?\n/);
    let currentEntry = null;
    let currentQuestion = null;

    const finishQuestion = () => {
        if (!currentQuestion) return;

        if (!currentQuestion.answers || currentQuestion.answers.length !== 4) {
            throw new Error(
                `Câu hỏi thiếu đủ 4 đáp án: ${currentQuestion.question.slice(0, 80)}`
            );
        }

        if (!currentQuestion.answer) {
            throw new Error(
                `Câu hỏi thiếu answer: ${currentQuestion.question.slice(0, 80)}`
            );
        }

        currentEntry.questions.push({
            question: currentQuestion.question,
            answers: currentQuestion.answers,
            correctIndex: findCorrectIndex(
                currentQuestion.answer,
                currentQuestion.answers
            )
        });

        currentQuestion = null;
    };

    const finishEntry = () => {
        finishQuestion();

        if (!currentEntry) return;

        if (currentEntry.questions.length !== 2) {
            throw new Error(
                `Hình ${currentEntry.filename} phải có đúng 2 câu hỏi, hiện có ${currentEntry.questions.length}`
            );
        }

        entries.push(currentEntry);
        currentEntry = null;
    };

    for (const rawLine of lines) {
        const line = rawLine.trim();
        if (!line) continue;

        const imageMatch = line.match(/^-\s*([^\s]+\.png)\s*:\s*$/i);
        if (imageMatch) {
            finishEntry();
            currentEntry = {
                filename: imageMatch[1],
                questions: []
            };
            continue;
        }

        const questionMatch = line.match(/^\d+\.\s*question:\s*(.*)$/i);
        if (questionMatch) {
            if (!currentEntry) {
                throw new Error('Câu hỏi xuất hiện trước filename hình ảnh.');
            }
            finishQuestion();
            currentQuestion = {
                question: questionMatch[1].trim(),
                answers: null,
                answer: null
            };
            continue;
        }

        if (!currentQuestion) continue;

        const options = parseAnswerOptions(line);
        if (options) {
            currentQuestion.answers = options;
            continue;
        }

        const answerMatch = line.match(/^answer:\s*(.*)$/i);
        if (answerMatch) {
            currentQuestion.answer = answerMatch[1].trim();
        }
    }

    finishEntry();
    return entries;
}

function mergeQuizContentIntoData(contentEntries) {
    const entriesByFilename = new Map(
        QUIZ_DATA.map(entry => [entry.image.split('/').pop(), entry])
    );

    const filenameAliases = new Map([
        ['missionary.png', 'missonary.png']
    ]);

    for (const contentEntry of contentEntries) {
        const fallbackFilename = filenameAliases.get(contentEntry.filename);
        const quizEntry =
            entriesByFilename.get(contentEntry.filename) ||
            entriesByFilename.get(fallbackFilename);

        if (!quizEntry) {
            throw new Error(
                `Không tìm thấy metadata hình ảnh trong QUIZ_DATA cho ${contentEntry.filename}`
            );
        }

        quizEntry.questions = contentEntry.questions;
    }

    if (contentEntries.length !== QUIZ_DATA.length) {
        throw new Error(
            `Số lượng hình không khớp: content=${contentEntries.length}, QUIZ_DATA=${QUIZ_DATA.length}`
        );
    }

    return QUIZ_DATA;
}

async function loadQuizDataFromContent() {
    const response = await fetch(QUIZ_CONTENT_PATH, { cache: 'no-store' });

    if (!response.ok) {
        throw new Error(
            `Không thể tải ${QUIZ_CONTENT_PATH}: HTTP ${response.status}`
        );
    }

    const contentEntries = parseQuizContent(await response.text());
    const quizData = mergeQuizContentIntoData(contentEntries);

    const totalQuestions = quizData.reduce(
        (total, entry) => total + entry.questions.length,
        0
    );

    if (totalQuestions !== 42) {
        throw new Error(`Expected 42 questions, received ${totalQuestions}`);
    }

    return quizData;
}
