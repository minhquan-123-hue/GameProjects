const assert = require('node:assert/strict');
const test = require('node:test');

const { parseQuizContent } = require('../src/data/quizContentLoader.js');

function contentFor(questionBlock) {
    return `images/\n- test.png:\nimage: ../assets/images/test.png\ncharacter: test\n${questionBlock}`;
}

function validQuestion(answer = 'right answer') {
    return [
        '1. question: Which answer is correct?',
        'a. wrong one b. right answer c. another one d. last one',
        `answer: ${answer}`
    ].join('\n');
}

test('content: accepts a valid question', () => {
    const result = parseQuizContent(contentFor(validQuestion()));

    assert.equal(result.entries.length, 1);
    assert.equal(result.entries[0].questions.length, 1);
    assert.equal(result.entries[0].questions[0].correctIndex, 1);
    assert.equal(result.validationErrors.length, 0);
});

test('content: skips a question with malformed answers', () => {
    const result = parseQuizContent(contentFor([
        '1. question: Missing option?',
        'a. only option',
        'answer: only option'
    ].join('\n')));

    assert.equal(result.entries.length, 0);
    assert.equal(result.validationErrors.length, 2);
    assert.match(result.validationErrors[0], /thiếu đủ 4 đáp án/);
    assert.match(result.validationErrors[1], /không có question hợp lệ/);
});

test('content: skips a question with an unknown answer', () => {
    const result = parseQuizContent(contentFor(validQuestion('not an option')));

    assert.equal(result.entries.length, 0);
    assert.equal(result.validationErrors.length, 2);
    assert.match(result.validationErrors[0], /Không xác định được đáp án đúng/);
    assert.match(result.validationErrors[1], /không có question hợp lệ/);
});

test('content: skips a character with no valid question', () => {
    const result = parseQuizContent(
        'images/\n- empty.png:\nimage: ../assets/images/empty.png\ncharacter: empty\n'
    );

    assert.equal(result.entries.length, 0);
    assert.equal(result.validationErrors.length, 1);
    assert.match(result.validationErrors[0], /không có question hợp lệ/);
});

class FakeElement {
    constructor() {
        this.listeners = {};
        this.classList = {
            values: new Set(),
            add: (...classes) => classes.forEach(className => this.classList.values.add(className)),
            remove: (...classes) => classes.forEach(className => this.classList.values.delete(className)),
            toggle: (className, force) => {
                if (force === undefined ? !this.classList.values.has(className) : force) {
                    this.classList.values.add(className);
                } else {
                    this.classList.values.delete(className);
                }
            },
            has: className => this.classList.values.has(className)
        };
        this.style = {};
    }

    addEventListener(event, handler) {
        this.listeners[event] = handler;
    }

    click() {
        this.listeners.click?.();
    }
}

function createFakeDocument() {
    const ids = [
        'menuScreen', 'introductionScreen', 'quizScreen', 'resultScreen',
        'btnStart', 'btnIntroduction', 'btnIntroductionClose', 'btnReplay',
        'characterImage', 'questionText', 'btnNext',
        'dickScore', 'pussyScore', 'masterScore',
        'resultTitle', 'resultMessage', 'resultScore',
        'resultDickScore', 'resultPussyScore', 'resultMasterScore'
    ];
    const elements = Object.fromEntries(ids.map(id => [id, new FakeElement()]));
    const answerBoxes = Array.from({ length: 4 }, () => new FakeElement());
    const selectors = {
        '.answer-box': answerBoxes,
        '.progress-text': [new FakeElement()],
        '.progress-fill': [new FakeElement()]
    };

    return {
        elements,
        addEventListener() {},
        getElementById: id => elements[id],
        querySelector: selector => selectors[selector]?.[0],
        querySelectorAll: selector => selectors[selector] || []
    };
}

test('navigation: supports Menu, Introduction, Quiz, Result and back to Menu', () => {
    global.document = createFakeDocument();
    const { GameUI } = require('../src/js/gameUI.js');
    const ui = new GameUI();
    const transitions = [];

    ui.bindNavigation({
        onStart: () => transitions.push('quiz'),
        onIntroduction: () => transitions.push('introduction'),
        onIntroductionClose: () => transitions.push('menu'),
        onReplay: () => transitions.push('menu')
    });

    document.getElementById('btnIntroduction').click();
    document.getElementById('btnStart').click();
    document.getElementById('btnReplay').click();
    document.getElementById('btnIntroductionClose').click();

    assert.deepEqual(transitions, ['introduction', 'quiz', 'menu', 'menu']);

    ui.showScreen('quiz');
    assert.equal(document.getElementById('quizScreen').classList.has('active'), true);
    assert.equal(document.getElementById('menuScreen').classList.has('active'), false);
    assert.equal(document.getElementById('introductionScreen').classList.has('active'), false);
    assert.equal(document.getElementById('resultScreen').classList.has('active'), false);
});

test('navigation: Game accepts only known screens', () => {
    global.document = createFakeDocument();
    const { Game } = require('../src/js/main.js');
    const rendered = [];
    const game = Object.create(Game.prototype);
    game.currentScreen = 'menu';
    game.renderScreen = () => rendered.push(game.currentScreen);

    game.switchScreen('introduction');
    game.switchScreen('quiz');
    game.switchScreen('result');
    game.switchScreen('menu');
    game.switchScreen('unknown');

    assert.deepEqual(rendered, ['introduction', 'quiz', 'result', 'menu']);
    assert.equal(game.currentScreen, 'menu');
});