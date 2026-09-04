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
                if (quiz === null) quiz = new Quiz(QUIZ_DATA, RESULT_TITLES);
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
    try {
        await loadQuizDataFromContent();
        console.log('Quiz data loaded from question-content.md successfully.');
    } catch (error) {
        console.error('Quiz content validation failed. Existing QUIZ_DATA will be used.', error);
    }

    game = new Game();
});
