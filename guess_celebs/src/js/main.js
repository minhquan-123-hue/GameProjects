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
        this.setupNavigation();
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

        // Nút chơi lại từ result
        const btnReplay = document.getElementById('btnReplay');
        if (btnReplay) {
            btnReplay.addEventListener('click', () => this.replayGame());
        }
    }

    /**
     * Chuyển đến màn hình tiếp theo
     * @param {string} screenName - Tên màn hình cần chuyển đến (menu, quiz, result)
     */
    switchScreen(screenName) {
        console.log(`Chuyển từ '${this.currentScreen}' sang '${screenName}'`);
        
        // Ẩn tất cả màn hình
        document.getElementById('menuScreen').style.display = 'none';
        document.querySelector('.quiz-screen').classList.remove('active');
        document.querySelector('.result-screen').classList.remove('active');

        // Hiển thị màn hình mới
        switch (screenName) {
            case 'menu':
                document.getElementById('menuScreen').style.display = 'block';
                break;
            case 'quiz':
                document.querySelector('.quiz-screen').classList.add('active');
                // Khởi tạo quiz nếu chưa có
                if (quiz === null) {
                    quiz = new Quiz(QUIZ_DATA, RESULT_TITLES);
                }
                break;
            case 'result':
                document.querySelector('.result-screen').classList.add('active');
                break;
        }

        this.currentScreen = screenName;
    }

    /**
     * Chơi lại game
     */
    replayGame() {
        if (quiz) {
            quiz.reset();
            this.switchScreen('quiz');
        }
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
