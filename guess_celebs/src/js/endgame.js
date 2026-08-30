/**
 * endgame.js
 * Quản lý màn hình kết thúc game
 * 
 * Trách nhiệm riêng biệt:
 * - Hiển thị kết quả dựa trên điểm số
 * - Quản lý result screen
 * - Không can thiệp vào logic quiz
 */

class Endgame {
    constructor(resultTitles) {
        this.resultTitles = resultTitles;
    }

    /**
     * Hiển thị kết quả game
     * @param {Object} scores - Object chứa {dick, pussy, master}
     */
    showResults(scores) {
        const totalScore = scores.dick + scores.pussy + scores.master;
        const resultData = this.resultTitles[totalScore] || this.resultTitles[5];

        // Hiển thị title, message và total score
        document.getElementById('resultTitle').textContent = resultData.title;
        document.getElementById('resultMessage').textContent = resultData.message;
        document.getElementById('resultScore').textContent = `Điểm: ${totalScore}/5`;

        // Hiển thị stickers cuối cùng
        document.getElementById('resultDickScore').textContent = scores.dick;
        document.getElementById('resultPussyScore').textContent = scores.pussy;
        document.getElementById('resultMasterScore').textContent = scores.master;

        // Chuyển sang result screen
        this.switchToResultScreen();
    }

    /**
     * Chuyển sang result screen
     */
    switchToResultScreen() {
        document.querySelector('.quiz-screen').classList.remove('active');
        document.querySelector('.result-screen').classList.add('active');
    }

    /**
     * Reset result screen (khi quay lại chơi lại)
     */
    reset() {
        document.querySelector('.result-screen').classList.remove('active');
    }
}

// Khởi tạo endgame khi cần thiết (được gọi từ main.js)
let endgame = null;
