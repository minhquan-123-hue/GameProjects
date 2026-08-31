/**
 * quizData.js
 * Dữ liệu câu hỏi quiz cho game
 * 
 * Cấu trúc mỗi câu hỏi:
 * - character: Tên diễn viên thực tế
 * - image: Đường dẫn tới hình ảnh
 * - question: Câu hỏi mô tả
 * - answers: Mảng 4 câu trả lời [A, B, C, D]
 * - correctIndex: Chỉ số câu trả lời đúng (0-3)
 */

const QUIZ_DATA = [
    {
        character: 'Gatut',
        image: '../assets/characters/gatuzz0_2.png',
        question: 'Sinh ra ở Tunisia, lớn lên chẳng có thảm đỏ nào trải sẵn, nhưng ông này vẫn bò lên thành ngôi sao của ngành. Nhìn mặt đoán tên đi, đừng làm như chưa từng nghe qua.',
        answers: [
            'Vũ Thánh Phúc',
            'Gatut',
            'Ngô Quý Dũng',
            'Trần Hữu Khoa'
        ],
        correctIndex: 1
    },
    {
        character: 'Johnny Sins',
        image: '../assets/characters/johnny_sins_2.png',
        question: 'Ông chú này nổi tiếng vì cái gì cũng cân: thợ điện, thợ nước, cảnh sát... nghề nào cũng nhảy vào làm như cuộc đời là cái CV không có mục “biết ngại”. Ai đây?',
        answers: [
            'Phạm Văn Dũng',
            'Johnny Sins',
            'Đinh Minh Tuấn',
            'Bùi Anh Kiên'
        ],
        correctIndex: 1
    },
    {
        character: 'Tokuda',
        image: '../assets/characters/tokuda_shigeo.png',
        question: 'Một huyền thoại người Nhật, nổi tiếng vì tuổi đời và cái sự nghiệp dài như danh sách việc phải làm cuối tuần. Nhìn phát là nhận ra ông cụ này chứ?',
        answers: [
            'Yamada Hiroshi',
            'Suzuki Masashi',
            'Tokuda',
            'Nakamura Kenji'
        ],
        correctIndex: 2
    },
    {
        character: 'Owen Gray',
        image: '../assets/characters/owen_gray.png',
        question: 'Ông này nổi tiếng vì nhiệt tình và năng lượng nhiều đến mức nhìn thôi cũng thấy mệt hộ. Ai đang mang cục pin vô hạn kia vậy?',
        answers: [
            'Hoàng Minh Sơn',
            'Owen Gray',
            'Lê Đức Hào',
            'Trương Văn Huy'
        ],
        correctIndex: 1
    },
    {
        character: 'Danny D',
        image: '../assets/characters/danny_D.png',
        question: 'Cái tên từng gắn với Brazzers này có một đặc điểm thể chất nổi bật đến mức gần như chẳng cần giới thiệu dài dòng. Thôi, nhìn ảnh rồi gọi đúng tên đi.',
        answers: [
            'Phạm Hoàng Minh',
            'Trần Quốc Bảo',
            'Danny D',
            'Lý Thanh Sơn'
        ],
        correctIndex: 2
    }
];

/**
 * Các tiêu đề hài hước dựa trên điểm số
 * Hiển thị ở màn hình kết thúc
 */
const RESULT_TITLES = {
    0: {
        title: '🤨 Còn Ngây Thơ',
        message: 'Bạn không biết gì cả! Hãy xem thêm và quay lại nhé!'
    },
    1: {
        title: '😐 Chư Đại Đế',
        message: 'Chỉ đúng 1 câu... Bạn cần học hỏi thêm nhiều!'
    },
    2: {
        title: '🤔 Người Hâm Mộ Sơ Cấp',
        message: 'Không tệ! Nhưng còn nhiều điều để khám phá.'
    },
    3: {
        title: '😏 Người Hâm Mộ Trung Cấp',
        message: 'Bạn biết khá nhiều rồi đó!'
    },
    4: {
        title: '🔥 Người Hâm Mộ Cao Cấp',
        message: 'Gần như là chuyên gia rồi!'
    },
    5: {
        title: '👑 ONLY FANS MASTER',
        message: 'Chúc mừng! Bạn là vua của Only Fans!'
    }
};
