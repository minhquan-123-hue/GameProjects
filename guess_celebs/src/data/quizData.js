/**
 * quizData.js
 * Dữ liệu 21 hình ảnh và question pool cho game.
 *
 * Mỗi hình ảnh có đúng 2 câu hỏi độc lập.
 * Nội dung question/answers/correctIndex để trống để điền thủ công.
 */

const createQuestionSlots = () => [
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
];

const QUIZ_DATA = [
    {
        character: 'Gatut',
        image: '../assets/characters/gatuzz0_2.png',
        questions: createQuestionSlots()
    },
    {
        character: 'Johnny Sins',
        image: '../assets/characters/johnny_sins_2.png',
        questions: createQuestionSlots()
    },
    {
        character: 'Tokuda',
        image: '../assets/characters/tokuda_shigeo.png',
        questions: createQuestionSlots()
    },
    {
        character: 'Owen Gray',
        image: '../assets/characters/owen_gray.png',
        questions: createQuestionSlots()
    },
    {
        character: 'Danny D',
        image: '../assets/characters/danny_D.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/characters/emi_fukada.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/characters/grand_teacher.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/characters/my.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/characters/yua_mikami.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/illness/gonorrhea.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/illness/hiv.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/illness/siphillis.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/position/cowgirl.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/position/doggy.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/position/missonary.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/position/sixnine.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/protection/condom.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/protection/creampie.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/protection/cumout.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/sextoy/anal_toy.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/sextoy/egg_vibrator.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/sextoy/fake_dick.png',
        questions: createQuestionSlots()
    },
    {
        character: '',
        image: '../assets/images/sextoy/fake_pussy.png',
        questions: createQuestionSlots()
    }
];

/**
 * Kết quả theo số câu đúng.
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
