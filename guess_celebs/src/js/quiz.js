/**
 * quiz.js
 * Xử lý logic quiz game
 * 
 * Chức năng:
 * - Quản lý flow quiz (hiển thị câu hỏi, xử lý câu trả lời)
 * - Tính điểm
 * - Hiển thị kết quả
 */

class Quiz {
    constructor(quizData, resultTitles) {
        this.quizData = quizData;
        this.resultTitles = resultTitles;
        this.currentQuestion = 0;
        this.scores = {
            dick: 0,
            pussy: 0,
            master: 0
        };
        this.answered = false;
        this.init();
    }

    /**
     * Khởi tạo quiz (chỉ setup, không load câu hỏi)
     */
    init() {
        this.setupEventListeners();
    }

    /**
     * Thiết lập event listeners
     */
    setupEventListeners() {
        const answerBoxes = document.querySelectorAll('.answer-box');
        answerBoxes.forEach((box, index) => {
            box.addEventListener('click', () => this.handleAnswer(index));
        });

        const btnNext = document.getElementById('btnNext');
        if (btnNext) {
            btnNext.addEventListener('click', () => this.nextQuestion());
        }
    }

    /**
     * Tải câu hỏi hiện tại
     */
    loadQuestion(index) {
        if (index >= this.quizData.length) {
            this.endQuiz();
            return;
        }

        const question = this.quizData[index];
        this.currentQuestion = index;
        this.answered = false;

        // Cập nhật progress
        this.updateProgress();

        // Hiển thị hình ảnh
        const imgElement = document.getElementById('characterImage');
        imgElement.src = question.image;
        imgElement.alt = question.character;

        // Hiển thị câu hỏi
        const questionText = document.getElementById('questionText');
        questionText.textContent = question.question;

        // Hiển thị đáp án
        const answerBoxes = document.querySelectorAll('.answer-box');
        answerBoxes.forEach((box, i) => {
            const labels = ['A', 'B', 'C', 'D'];
            box.innerHTML = `<span class="answer-label">${labels[i]}</span> ${question.answers[i]}`;
            box.classList.remove('correct', 'incorrect', 'disabled');
            box.style.pointerEvents = 'auto';
        });

        // Ẩn nút Next
        const btnNext = document.getElementById('btnNext');
        btnNext.classList.remove('show');
    }

    /**
     * Cập nhật thanh tiến độ
     */
    updateProgress() {
        const progress = ((this.currentQuestion) / this.quizData.length) * 100;
        const progressFill = document.querySelector('.progress-fill');
        progressFill.style.width = progress + '%';

        const progressText = document.querySelector('.progress-text');
        progressText.textContent = `Câu ${this.currentQuestion + 1}/${this.quizData.length}`;
    }

    /**
     * Xử lý câu trả lời
     */
    handleAnswer(selectedIndex) {
        if (this.answered) return;

        this.answered = true;
        const question = this.quizData[this.currentQuestion];
        const answerBoxes = document.querySelectorAll('.answer-box');

        // Vô hiệu hóa tất cả đáp án
        answerBoxes.forEach(box => {
            box.classList.add('disabled');
            box.style.pointerEvents = 'none';
        });

        // Kiểm tra đáp án
        if (selectedIndex === question.correctIndex) {
            answerBoxes[selectedIndex].classList.add('correct');
            this.addScore();
            // Play correct sound
            if (audioManager) {
                audioManager.playCorrect();
            }
        } else {
            answerBoxes[selectedIndex].classList.add('incorrect');
            answerBoxes[question.correctIndex].classList.add('correct');
            // Play wrong sound
            if (audioManager) {
                audioManager.playWrong();
            }
        }

        // Hiển thị nút Next
        const btnNext = document.getElementById('btnNext');
        btnNext.classList.add('show');

        // Cập nhật hiển thị điểm
        this.updateScoreDisplay();
    }

    /**
     * Thêm điểm dựa trên vòng
     */
    addScore() {
        const round = this.currentQuestion + 1;
        if (round % 3 === 1) {
            this.scores.dick++;
        } else if (round % 3 === 2) {
            this.scores.pussy++;
        } else {
            this.scores.master++;
        }
    }

    /**
     * Cập nhật hiển thị điểm
     */
    updateScoreDisplay() {
        document.getElementById('dickScore').textContent = this.scores.dick;
        document.getElementById('pussyScore').textContent = this.scores.pussy;
        document.getElementById('masterScore').textContent = this.scores.master;
    }

    /**
     * Chuyển sang câu hỏi tiếp theo
     */
    nextQuestion() {
        // Play Mon Wave sound khi chuyển câu
        if (audioManager) {
            audioManager.playNextQuestion();
        }
        this.loadQuestion(this.currentQuestion + 1);
    }

    /**
     * Kết thúc quiz - gọi endgame để hiển thị kết quả
     * Trách nhiệm: Chuyển điểm cho endgame, endgame sẽ xử lý hiển thị
     */
    endQuiz() {
        if (endgame === null) {
            endgame = new Endgame(RESULT_TITLES);
        }
        endgame.showResults(this.scores);
    }

    /**
     * Reset state để chơi lại từ đầu
     * Hàm này chỉ reset dữ liệu, KHÔNG load câu hỏi
     * Loading câu hỏi đầu sẽ xảy ra khi startGame() được gọi
     */
    resetState() {
        this.currentQuestion = 0;
        this.scores = { dick: 0, pussy: 0, master: 0 };
        this.answered = false;
        console.log('Quiz state đã được reset');
    }

    /**
     * Bắt đầu game (load câu hỏi đầu tiên)
     * Được gọi khi chuyển đến quiz screen
     * setupEventListeners() đã được gọi trong init()
     */
    startGame() {
        console.log('Game started - loading question 1');
        this.loadQuestion(0);
    }
}

// Khởi tạo quiz khi cần thiết (được gọi từ main.js khi chuyển sang quiz screen)
let quiz = null;
