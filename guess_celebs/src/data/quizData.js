/**
 * quizData.js
 * Dữ liệu nhân vật và question pool cho game.
 *
 * Mỗi nhân vật có 2 câu hỏi độc lập.
 * Nội dung question/answers/correctIndex để trống để điền thủ công.
 */

const QUIZ_DATA = [
    {
        character: 'Gatut',
        image: '../assets/characters/gatuzz0_2.png',
        questions: [
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            },
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            }
        ]
    },
    {
        character: 'Johnny Sins',
        image: '../assets/characters/johnny_sins_2.png',
        questions: [
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            },
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            }
        ]
    },
    {
        character: 'Tokuda',
        image: '../assets/characters/tokuda_shigeo.png',
        questions: [
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            },
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            }
        ]
    },
    {
        character: 'Owen Gray',
        image: '../assets/characters/owen_gray.png',
        questions: [
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            },
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            }
        ]
    },
    {
        character: 'Danny D',
        image: '../assets/characters/danny_D.png',
        questions: [
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            },
            {
                question: '',
                answers: ['', '', '', ''],
                correctIndex: null
            }
        ]
    }
];

/**
 * Kết quả theo số câu đúng.
 * Title/message để trống để điền thủ công.
 */
const RESULT_TITLES = {
    0: {
        title: '💀',
        message: ''
    },
    1: {
        title: '🍆',
        message: ''
    },
    2: {
        title: '🗿',
        message: ''
    },
    3: {
        title: '🥵',
        message: ''
    },
    4: {
        title: '🤡',
        message: ''
    },
    5: {
        title: '👑',
        message: ''
    }
};
