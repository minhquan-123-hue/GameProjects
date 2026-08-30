/**
 * main.js
 * File chính điều phối toàn bộ game
 * 
 * Cấu trúc:
 * - Quản lý trạng thái game (menu, playing, gameover)
 * - Điều hướng giữa các màn hình
 * - Khởi tạo game
 */

class Game {
    constructor() {
        this.currentScreen = 'menu';
        this.gameState = {};
        this.init();
    }

    init() {
        console.log('Game đã khởi tạo');
        // Khởi tạo game ở đây
    }

    /**
     * Chuyển đến màn hình tiếp theo
     * @param {string} screenName - Tên màn hình cần chuyển đến
     */
    switchScreen(screenName) {
        console.log(`Chuyển từ '${this.currentScreen}' sang '${screenName}'`);
        this.currentScreen = screenName;
        // TODO: Xử lý logic chuyển màn hình
    }

    /**
     * Bắt đầu game
     */
    startGame() {
        this.switchScreen('playing');
    }

    /**
     * Kết thúc game
     */
    endGame() {
        this.switchScreen('gameover');
    }
}

// Khởi tạo game khi trang load
let game;
document.addEventListener('DOMContentLoaded', function() {
    game = new Game();
});
