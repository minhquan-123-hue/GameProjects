/**
 * main.js
 * File chính điều phối toàn bộ game
 *
 * Cấu trúc:
 * - Quản lý trạng thái game (menu, quiz, result)
 * - Điều hướng giữa các màn hình
 * - Khởi tạo quiz khi cần
 */

const QUIZ_CONTENT_PATH = '../content/question-content.md';

function normalizeQuizText(value) {
    return String(value || '')
        .normalize('NFD')
        .replace(/[\u0300-\u036f]/g, '')
        .toLowerCase()
        .replace(/[`"“”'’]/g, '')
        .replace(/\s+/g, ' ')
        .trim();
}

function parseAnswerOptions(line) {
    const matches = [...line.matchAll(/(?:^|\s)([a-d])\.\s*/gi)];
    if (matches.length !== 4 || matches.map(match => match[1].toLowerCase()).join('') !== 'abcd') {
        return null;
    }

    return matches.map((match, index) => {
        const start = match.index + match[0].length;
        const end = index < matches.length - 1 ? matches[index + 1].index : line.length;
        return line.slice(start, end).trim();
    });
}

function parseQuizContent(markdown) {
    const lines = markdown.split(/\r?\n/);
    const entries = [];
    let currentEntry = null;
    let currentQuestion = null;

    const finishQuestion = () => {
        if (!currentQuestion) return;
        if (!currentQuestion.answers || currentQuestion.answers.length !== 4) {
            throw new Error(`Câu hỏi thiếu đủ 4 đáp án: ${currentQuestion.question.slice(0, 60)}`);
        }
        if (!currentQuestion.answer) {
            throw new Error(`Câu hỏi thiếu dòng answer: ${currentQuestion.question.slice(0, 60)}`);
        }

        const normalizedAnswer = normalizeQuizText(currentQuestion.answer);
        const correctIndex = currentQuestion.answers.findIndex(
            answer => normalizeQuizText(answer) === normalizedAnswer
        );

        if (correctIndex === -1) {
            throw new Error(
                `Answer không khớp với 4 lựa chọn: "${currentQuestion.answer}" | câu: ${currentQuestion.question.slice(0, 80)}`
            );
        }

        currentEntry.questions.push({
            question: currentQuestion.question,
            answers: currentQuestion.answers,
            correctIndex
        });
        currentQuestion = null;
    };

    const finishEntry = () => {
        finishQuestion();
        if (currentEntry) {
            if (currentEntry.questions.length !== 2) {
                throw new Error(`Hình ${currentEntry.filename} phải có đúng 2 câu hỏi, hiện có ${currentEntry.questions.length}`);
            }
            entries.push(currentEntry);
        }
        currentEntry = null;
    };

    for (const rawLine of lines) {
        const line = rawLine.trim();
        if (!line) continue;

        const imageMatch = line.match(/^-\s*([^\s]+\.png)\s*:\s*$/i);
        if (imageMatch) {
            finishEntry();
            currentEntry = { filename: imageMatch[1], questions: [] };
            continue;
        }

        const questionMatch = line.match(/^\d+\.\s*question:\s*(.*)$/i);
        if (questionMatch) {
            if (!currentEntry) throw new Error('Phát hiện câu hỏi nhưng chưa có hình ảnh tương ứng.');
            finishQuestion();
            currentQuestion = { question: questionMatch[1].trim(), answers: null, answer: null };
            continue;
        }

        if (!currentQuestion) continue;

        const answers = parseAnswerOptions(line);
        if (answers) {
            currentQuestion.answers = answers;
            continue;
        }

        const answerMatch = line.match(/^answer:\s*(.*)$/i);
        if (answerMatch) currentQuestion.answer = answerMatch[1].trim();
    }

    finishEntry();
    return entries;
}

function buildQuizDataFromContent(contentEntries, fallbackData) {
    const fallbackByFilename = new Map(
        fallbackData.map(entry => [entry.image.split('/').pop(), entry])
    );
    const aliases = new Map([['missionary.png', 'missonary.png']]);

    return contentEntries.map(entry => {
        const fallback = fallbackByFilename.get(entry.filename) || fallbackByFilename.get(aliases.get(entry.filename));
        if (!fallback) throw new Error(`Không tìm thấy metadata/image tương ứng cho ${entry.filename}`);
        return { character: fallback.character, image: fallback.image, questions: entry.questions };
    });
}

async function loadQuizDataFromContent() {
    const response = await fetch(QUIZ_CONTENT_PATH, { cache: 'no-store' });
    if (!response.ok) throw new Error(`Không thể tải ${QUIZ_CONTENT_PATH}: HTTP ${response.status}`);

    const contentEntries = parseQuizContent(await response.text());
    const quizData = buildQuizDataFromContent(contentEntries, QUIZ_DATA);
    if (quizData.length !== QUIZ_DATA.length) {
        throw new Error(`Số lượng hình không khớp: content=${quizData.length}, fallback=${QUIZ_DATA.length}`);
    }
    return quizData;
}

class Game {
    constructor(quizData) {
        this.currentScreen = 'menu';
        this.gameState = {};
        this.quizData = quizData;
        this.init();
    }

    init() {
        console.log('Game đã khởi tạo');
        if (audioManager === null) audioManager = new AudioManager();
        this.setupNavigation();
        this.updateScreenState('menu');
    }

    setupNavigation() {
        const btnStart = document.getElementById('btnStart');
        if (btnStart) btnStart.addEventListener('click', () => this.switchScreen('quiz'));

        const btnIntroduction = document.getElementById('btnIntroduction');
        if (btnIntroduction) btnIntroduction.addEventListener('click', () => this.switchScreen('introduction'));

        const btnIntroductionClose = document.getElementById('btnIntroductionClose');
        if (btnIntroductionClose) btnIntroductionClose.addEventListener('click', () => this.switchScreen('menu'));

        const btnReplay = document.getElementById('btnReplay');
        if (btnReplay) btnReplay.addEventListener('click', () => this.replayGame());
    }

    updateScreenState(screenName) {
        document.body.classList.remove('screen-menu', 'screen-quiz', 'screen-result');
        document.body.classList.add(`screen-${screenName}`);
    }

    switchScreen(screenName) {
        console.log(`Chuyển từ '${this.currentScreen}' sang '${screenName}'`);
        this.updateScreenState(screenName);
        document.getElementById('menuScreen').style.display = 'none';
        document.querySelector('.introduction-screen').style.display = 'none';
        document.querySelector('.quiz-screen').classList.remove('active');
        document.querySelector('.result-screen').classList.remove('active');

        switch (screenName) {
            case 'menu':
                document.getElementById('menuScreen').style.display = 'block';
                break;
            case 'introduction':
                document.getElementById('introductionScreen').style.display = 'block';
                break;
            case 'quiz':
                document.querySelector('.quiz-screen').classList.add('active');
                if (quiz === null) quiz = new Quiz(this.quizData, RESULT_TITLES);
                quiz.startGame();
                break;
            case 'result':
                document.querySelector('.result-screen').classList.add('active');
                break;
        }
        this.currentScreen = screenName;
    }

    replayGame() {
        if (quiz) quiz.resetState();
        if (endgame) endgame.reset();
        this.switchScreen('menu');
    }

    startGame() { this.switchScreen('quiz'); }
    endGame() { this.switchScreen('result'); }
}

let game;
document.addEventListener('DOMContentLoaded', async function() {
    let activeQuizData = QUIZ_DATA;
    try {
        activeQuizData = await loadQuizDataFromContent();
        console.log(`Quiz content loaded successfully: ${activeQuizData.length} images / ${activeQuizData.length * 2} questions`);
    } catch (error) {
        console.error('Quiz content validation failed. Using existing QUIZ_DATA as fallback.', error);
    }
    game = new Game(activeQuizData);
});
