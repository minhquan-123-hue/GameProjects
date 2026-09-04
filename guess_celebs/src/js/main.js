/**
 * main.js
 * File chính điều phối toàn bộ game
 *
 * Cấu trúc:
 * - Quản lý trạng thái game (menu, introduction, quiz, result)
 * - Điều hướng giữa các màn hình
 * - Khởi tạo quiz khi cần
 */

const SCREEN_NAMES = ['menu', 'introduction', 'quiz', 'result'];

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
        this.renderScreen();
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

    switchScreen(screenName) {
        if (!SCREEN_NAMES.includes(screenName)) {
            console.error(`Màn hình không hợp lệ: '${screenName}'`);
            return;
        }

        console.log(`Chuyển từ '${this.currentScreen}' sang '${screenName}'`);
        this.currentScreen = screenName;
        this.renderScreen();
    }

    renderScreen() {
        const screens = {
            menu: document.getElementById('menuScreen'),
            introduction: document.getElementById('introductionScreen'),
            quiz: document.querySelector('.quiz-screen'),
            result: document.querySelector('.result-screen')
        };

        Object.entries(screens).forEach(([name, element]) => {
            if (!element) return;
            element.classList.toggle('active', name === this.currentScreen);
        });

        document.body.classList.remove(...SCREEN_NAMES.map(name => `screen-${name}`));
        document.body.classList.add(`screen-${this.currentScreen}`);

        if (this.currentScreen === 'quiz') {
            if (quiz === null) quiz = new Quiz(QUIZ_DATA, RESULT_TITLES);
            quiz.startGame();
        }
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
        console.log('Quiz content loaded successfully.');
        game = new Game();
    } catch (error) {
        console.error('Quiz content failed to load. Game startup aborted.', error);
    }
});
