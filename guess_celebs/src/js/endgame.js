/**
 * endgame.js
 * Quản lý màn hình kết thúc game
 *
 * Trách nhiệm riêng biệt:
 * - Hiển thị kết quả dựa trên điểm số
 * - Quản lý result screen
 * - Không can thiệp vào logic quiz
 */

const RESULT_TITLES = {
    0: {
        title: '💀',
        message: 'Cậu nhỏ xuất nhanh , 1 tháng được tầm quả lọ'
    },
    1: {
        title: '🍆',
        message: 'Cậu bé khổ dâm, thích nhịn xuất nhưng hay mộng tinh'
    },
    2: {
        title: '🗿',
        message: 'Dâm tặc nửa vời, bắn toàn vào điện thoại'
    },
    3: {
        title: '🥵',
        message: 'Dái lắm lông , xuất tinh vào quần sịp xong đi ngủ'
    },
    4: {
        title: '🤡',
        message: 'Ăn Ba tô cơm, xúc bình xăng con 5 lần một tuần'
    },
    5: {
        title: '👑',
        message: 'Vua sục cặc của lớp'
    }
};

class Endgame {
    constructor(resultTitles, ui) {
        this.resultTitles = resultTitles;
        this.ui = ui;
    }

    /**
     * Hiển thị kết quả game
     * @param {Object} scores - Object chứa {dick, pussy, master}
     */
    showResults(scores, totalQuestions) {
        const totalScore = scores.dick + scores.pussy + scores.master;
        const resultData = this.resultTitles[totalScore] || this.resultTitles[5];

        this.ui.renderResult(resultData, scores, totalQuestions);

        if (audioManager) {
            audioManager.playFinalRound();
        }
    }

    reset() {
    }
}

let endgame = null;
