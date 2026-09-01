/**
 * main.js
 * File chính điều phối toàn bộ game
 * 
 * Cấu trúc:
 * - Quản lý trạng thái game (menu, quiz, result)
 * - Điều hướng giữa các màn hình
 * - Khởi tạo quiz khi cần
 */

class Game {
    constructor() {
        this.currentScreen = 'menu';
        this.gameState = {};
        this.init();
    }

    init() {
        console.log('Game đã khởi tạo');
        // Khởi tạo audio manager
        if (audioManager === null) {
            audioManager = new AudioManager();
        }
        this.setupNavigation();
        this.updateScreenState('menu');
    }

    /**
     * Thiết lập navigation
     */
    setupNavigation() {
        // Nút bắt đầu từ menu
        const btnStart = document.getElementById('btnStart');
        if (btnStart) {
            btnStart.addEventListener('click', () => this.switchScreen('quiz'));
        }

        // Nút giới thiệu
        const btnIntroduction = document.getElementById('btnIntroduction');
        if (btnIntroduction) {
            btnIntroduction.addEventListener('click', () => this.switchScreen('introduction'));
        }

        const btnIntroductionClose = document.getElementById('btnIntroductionClose');
        if (btnIntroductionClose) {
            btnIntroductionClose.addEventListener('click', () => this.switchScreen('menu'));
        }

        // Nút chơi lại từ result
        const btnReplay = document.getElementById('btnReplay');
        if (btnReplay) {
            btnReplay.addEventListener('click', () => this.replayGame());
        }
    }

    /**
     * Cập nhật trạng thái visual của toàn viewport.
     * CSS sử dụng class này để chuyển background giữa các màn hình.
     */
    updateScreenState(screenName) {
        document.body.classList.remove('screen-menu', 'screen-quiz', 'screen-result');
        document.body.classList.add(`screen-${screenName}`);
    }

    /**
     * Chuyển đến màn hình tiếp theo
     * Trách nhiệm: Chỉ quản lý hiển thị/ẩn màn hình, không can thiệp vào logic quiz
     * @param {string} screenName - Tên màn hình cần chuyển đến (menu, quiz, result, introduction)
     */
    switchScreen(screenName) {
        console.log(`Chuyển từ '${this.currentScreen}' sang '${screenName}'`);

        // Cập nhật visual state trước khi hiển thị màn hình mới
        this.updateScreenState(screenName);
        
        // Ẩn tất cả màn hình
        document.getElementById('menuScreen').style.display = 'none';
        document.querySelector('.introduction-screen').style.display = 'none';
        document.querySelector('.quiz-screen').classList.remove('active');
        document.querySelector('.result-screen').classList.remove('active');

        // Hiển thị màn hình mới
        switch (screenName) {
            case 'menu':
                document.getElementById('menuScreen').style.display = 'block';
                break;
            case 'introduction':
                document.getElementById('introductionScreen').style.display = 'block';
                break;
            case 'quiz':
                document.querySelector('.quiz-screen').classList.add('active');
                // Khởi tạo quiz nếu chưa có
                if (quiz === null) {
                    quiz = new Quiz(QUIZ_DATA, RESULT_TITLES);
                }
                // Bắt đầu game: load câu hỏi đầu tiên
                quiz.startGame();
                break;
            case 'result':
                document.querySelector('.result-screen').classList.add('active');
                break;
        }

        this.currentScreen = screenName;
    }

    /**
     * Chơi lại game
     * Trách nhiệm: Reset state quiz + reset endgame + quay lại menu
     * Luồng: user ấn "Quay lại để xuất thêm" → reset state → hiển thị menu
     *        user ấn "xuất" lại ở menu → startGame() load câu 1 mới
     */
    replayGame() {
        if (quiz) {
            quiz.resetState();  // Reset điểm và câu hỏi hiện tại
        }
        if (endgame) {
            endgame.reset();    // Reset result screen
        }
        this.switchScreen('menu');  // Quay lại menu (KHÔNG phải quiz)
    }

    /**
     * Bắt đầu game
     */
    startGame() {
        this.switchScreen('quiz');
    }

    /**
     * Kết thúc game
     */
    endGame() {
        this.switchScreen('result');
    }
}

// Khởi tạo game khi trang load
let game;
document.addEventListener('DOMContentLoaded', function() {
    game = new Game();
});
