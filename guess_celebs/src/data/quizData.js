/**
 * quizData.js
 * Dữ liệu 21 hình ảnh và question pool cho game.
 *
 * Mỗi hình ảnh có đúng 2 câu hỏi độc lập.
 */

const QUIZ_DATA = [
    {
        character: 'Gatut',
        image: '../assets/images/characters/gatuzz0_2.png',
        questions: [
            { question: 'Gatut nhìn mặt thì hiền, nhưng cái tên nghe cứ như một tiếng động phát ra sau khi ai đó vừa làm chuyện không nên làm. Gatut là ai?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu nghề nghiệp được đo bằng độ xuất hiện trên màn hình của người lớn, Gatut thuộc hệ nào?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: 'Johnny Sins',
        image: '../assets/images/characters/johnny_sins_2.png',
        questions: [
            { question: 'Johnny Sins là người đàn ông nổi tiếng với khả năng biến một ngày bình thường thành CV dài hơn cả Wikipedia. Anh ta nổi tiếng vì điều gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu thấy Johnny Sins xuất hiện trong một bộ phim, câu hỏi đầu tiên của bạn nên là “anh này đóng vai gì?” hay “lần này anh ấy lại làm nghề gì?”', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: 'Tokuda',
        image: '../assets/images/characters/tokuda_shigeo.png',
        questions: [
            { question: 'Tokuda là cái tên khiến Google biết nhiều chuyện mà bố mẹ bạn tốt nhất không nên biết. Ông nổi tiếng trong lĩnh vực nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nhìn Tokuda, bạn sẽ nghĩ đây là giáo viên về hưu, ông hàng xóm hiền lành, hay một nhân vật có CV khiến HR phải uống nước?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: 'Emi Fukada',
        image: '../assets/images/characters/emi_fukada.png',
        questions: [
            { question: 'Emi Fukada là cái tên thuộc lĩnh vực giải trí người lớn. Cô được biết đến với vai trò nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu CV của Emi Fukada có mục “kinh nghiệm làm việc”, bạn đoán mục đó sẽ thuộc ngành giải trí nào?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: 'Grand Teacher',
        image: '../assets/images/characters/grand_teacher.png',
        questions: [
            { question: 'Nhìn cái tên `grand_teacher.png`, đây là kiểu giáo viên mà học sinh nên ngoan ngoãn ngồi học hay một nhân vật có “giáo án” rất đáng ngờ?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu `grand_teacher.png` được tuyển vào trường, bạn nghĩ môn học nào sẽ khiến phụ huynh muốn họp khẩn?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: 'Yua Mikami',
        image: '../assets/images/characters/yua_mikami.png',
        questions: [
            { question: 'Yua Mikami là một cái tên nổi tiếng trong ngành giải trí người lớn. Cô được biết đến với vai trò nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu Yua Mikami đổi nghề sang một công việc văn phòng bình thường, điều gì sẽ khiến đồng nghiệp bất ngờ nhất?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: 'My',
        image: '../assets/images/characters/my.png',
        questions: [
            { question: 'Nhân vật trong ảnh có tên là My. Bạn có nhận ra cô ấy là ai không?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu nhìn vào ảnh và filename `my.png`, tên của nhân vật này là gì?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/illness/gonorrhea.png',
        questions: [
            { question: '`gonorrhea` là loại khách không mời mà đến, đã đến còn để lại quà. Đây là bệnh gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu bệnh lậu có thể gửi lời nhắn, câu nào hợp nhất: “Xin chào”, “Tôi nhớ bạn”, hay “Chúng ta cần nói chuyện”?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/illness/hiv.png',
        questions: [
            { question: 'HIV là viết tắt của cụm từ nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'HIV không phải thứ để đùa cợt ngoài đời. Vậy kiến thức nào giúp giảm nguy cơ lây truyền nó?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/illness/siphillis.png',
        questions: [
            { question: '`siphillis` nhìn tên đã thấy giống một con boss trong game mà bạn tuyệt đối không muốn unlock. Nó là bệnh gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu giang mai có nút “Undo”, có lẽ nhân loại đã spam nút đó từ rất lâu. Bệnh này thuộc nhóm bệnh nào?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/position/cowgirl.png',
        questions: [
            { question: '`cowgirl` nghe như một nghề ở miền Tây nước Mỹ, nhưng trong game này lại là một tư thế nổi tiếng. Nó là gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu đặt tên các tư thế quan hệ theo nghề nghiệp, `cowgirl` rõ ràng đã chọn đúng ngành có đồng phục tưởng tượng khá đặc biệt. Nó ám chỉ tư thế nào?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/position/doggy.png',
        questions: [
            { question: '`doggy` nghe như tên một chú chó ngoan, nhưng trong ngữ cảnh người lớn thì nó chẳng liên quan gì đến việc dắt chó đi dạo. Đây là tư thế nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu ai đó nói “tối nay chơi doggy”, bạn nên chuẩn bị dây xích cho chó hay hiểu rằng họ đang nói chuyện người lớn?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/position/missonary.png',
        questions: [
            { question: '`missionary` nghe giống người đi truyền giáo, nhưng trong phòng ngủ thì nghĩa lại khác hoàn toàn. Đây là tư thế nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu một nhà truyền giáo nghe thấy từ “missionary” trong cuộc trò chuyện này, họ có thể sẽ cần hỏi lại: “Khoan, chúng ta đang nói về cái gì?”', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/position/sixnine.png',
        questions: [
            { question: '`sixnine` là cái tên mà khi viết cạnh nhau tự nhiên trở nên đáng ngờ một cách không cần thiết. Nó ám chỉ điều gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu giáo viên toán hỏi “69 là gì?”, bạn có thể trả lời đúng toán học, nhưng tại sao cả lớp lại bắt đầu cười?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/protection/condom.png',
        questions: [
            { question: '`condom` là món đồ nhỏ bé nhưng gánh trên vai một lượng trách nhiệm lớn hơn vẻ ngoài của nó. Nó dùng để làm gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Có những thứ càng rẻ càng không nên tiết kiệm. Bao cao su có phải một trong số đó không?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/protection/creampie.png',
        questions: [
            { question: '`creampie` nghe như món bánh ở tiệm dessert, nhưng chắc chắn không phải thứ bạn nên gọi ở quầy bánh. Trong ngữ cảnh người lớn, thuật ngữ này ám chỉ điều gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu nhìn thấy file `creampie.png` trong folder “protection”, bạn có nghĩ người đặt tên folder này đang rất lạc quan không?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/protection/cumout.png',
        questions: [
            { question: '`cumout` nghe như một khẩu hiệu thể thao rất đáng ngờ. Trong ngữ cảnh tình dục, nó liên quan đến phương pháp tránh thai nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Có một phương pháp mà người ta nghĩ “chắc kịp”. Vấn đề là cơ thể con người không phải ứng dụng có nút Cancel. Đó là phương pháp nào?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/sextoy/anal_toy.png',
        questions: [
            { question: '`anal_toy` nghe khá thẳng thắn, gần như không cho người đọc cơ hội giả vờ không hiểu. Nó thuộc nhóm đồ chơi nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu một món đồ có chữ “anal” ngay trong tên file, bạn có cần mở Photoshop để đoán mục đích sử dụng nữa không?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/sextoy/egg_vibrator.png',
        questions: [
            { question: '`egg_vibrator` nghe như một quả trứng đã quyết định từ bỏ nghề làm bữa sáng. Đây là loại đồ chơi gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu quả trứng này xuất hiện trong tủ lạnh, bạn có nên luộc nó không?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/sextoy/fake_dick.png',
        questions: [
            { question: '`fake_dick` là một cái tên có độ vòng vo gần bằng số 0. Nó dùng để chỉ loại sản phẩm nào?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu ai đó nói “đây không phải thật”, nhưng filename lại là `fake_dick.png`, Sherlock Holmes có cần xuất hiện không?', answers: ['', '', '', ''], correctIndex: null }
        ]
    },
    {
        character: '',
        image: '../assets/images/sextoy/fake_pussy.png',
        questions: [
            { question: '`fake_pussy` cũng thuộc trường phái đặt tên “nói thẳng cho đỡ mất thời gian”. Nó là sản phẩm gì?', answers: ['', '', '', ''], correctIndex: null },
            { question: 'Nếu filename đã nói hết đáp án, câu hỏi này có còn gọi là quiz không hay chỉ là bài kiểm tra khả năng đọc tiếng Anh?', answers: ['', '', '', ''], correctIndex: null }
        ]
    }
];

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
