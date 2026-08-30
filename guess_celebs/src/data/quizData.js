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
        question: 'Diễn viên này sinh ra ở Tunisia, lớn lên trong hoàn cảnh khó khăn, nhưng đã trở thành một ngôi sao nổi tiếng trong ngành. Ai là anh ta?',
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
        question: 'Tên tuổi này nổi tiếng vì làm việc ở rất nhiều nghề khác nhau: thợ sửa điện, thợ sửa nước, cảnh sát... Ai là anh ta?',
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
        question: 'Diễn viên người Nhật Bản này nổi tiếng vì tuổi tác của mình và sự nghiệp dài lâu trong ngành. Ai là anh ta?',
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
        question: 'Diễn viên này nổi tiếng vì nhiệt tình và năng lượng khổng lồ trong công việc. Ai là anh ta?',
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
        question: 'Diễn viên nổi tiếng liên kết với Brazzers và có một đặc điểm thể chất rất nổi bật. Ai là anh ta?',
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
