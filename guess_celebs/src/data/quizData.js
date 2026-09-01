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
            { question: 'Gatut nhìn mặt thì hiền, nhưng cái tên nghe cứ như một tiếng động phát ra sau khi ai đó vừa làm chuyện không nên làm. Gatut là ai?', answers: ['Một diễn viên', 'Một người mẫu', 'Một diễn viên phim người lớn', 'Một ca sĩ'], correctIndex: 2 },
            { question: 'Nếu nghề nghiệp được đo bằng độ xuất hiện trên màn hình của người lớn, Gatut thuộc hệ nào?', answers: ['Người mẫu thời trang', 'Diễn viên phim người lớn', 'Streamer', 'Nhạc sĩ'], correctIndex: 1 }
        ]
    },
    {
        character: 'Johnny Sins',
        image: '../assets/images/characters/johnny_sins_2.png',
        questions: [
            { question: 'Johnny Sins là người đàn ông nổi tiếng với khả năng biến một ngày bình thường thành CV dài hơn cả Wikipedia. Anh ta nổi tiếng vì điều gì?', answers: ['Làm nhiều nghề trong các bộ phim người lớn', 'Là cầu thủ bóng đá', 'Là ca sĩ', 'Là chính trị gia'], correctIndex: 0 },
            { question: 'Nếu thấy Johnny Sins xuất hiện trong một bộ phim, câu hỏi đầu tiên của bạn nên là “anh này đóng vai gì?” hay “lần này anh ấy lại làm nghề gì?”', answers: ['Đúng, đó là điểm nổi tiếng của anh ấy', 'Không, anh ấy chỉ đóng phim hành động', 'Không, anh ấy là diễn viên Hollywood', 'Không, anh ấy chỉ làm người mẫu'], correctIndex: 0 }
        ]
    },
    {
        character: 'Tokuda',
        image: '../assets/images/characters/tokuda_shigeo.png',
        questions: [
            { question: 'Tokuda là cái tên khiến Google biết nhiều chuyện mà bố mẹ bạn tốt nhất không nên biết. Ông nổi tiếng trong lĩnh vực nào?', answers: ['Giáo dục', 'Điện ảnh', 'Giải trí người lớn', 'Thể thao'], correctIndex: 2 },
            { question: 'Nhìn Tokuda, bạn sẽ nghĩ đây là giáo viên về hưu, ông hàng xóm hiền lành, hay một nhân vật có CV khiến HR phải uống nước?', answers: ['Giáo viên về hưu', 'Diễn viên phim người lớn người Nhật', 'Chính trị gia', 'Nhà khoa học'], correctIndex: 1 }
        ]
    },
    {
        character: 'Emi Fukada',
        image: '../assets/images/characters/emi_fukada.png',
        questions: [
            { question: 'Emi Fukada là cái tên thuộc lĩnh vực giải trí người lớn. Cô được biết đến với vai trò nào?', answers: ['Ca sĩ', 'Diễn viên phim người lớn', 'Nhà báo', 'Vận động viên'], correctIndex: 1 },
            { question: 'Nếu CV của Emi Fukada có mục “kinh nghiệm làm việc”, bạn đoán mục đó sẽ thuộc ngành giải trí nào?', answers: ['Điện ảnh Hollywood', 'Âm nhạc', 'Giải trí người lớn', 'Thời trang'], correctIndex: 2 }
        ]
    },
    {
        character: 'Grand Teacher',
        image: '../assets/images/characters/grand_teacher.png',
        questions: [
            { question: 'Nhìn cái tên `grand_teacher.png`, đây là kiểu giáo viên mà học sinh nên ngoan ngoãn ngồi học hay một nhân vật có “giáo án” rất đáng ngờ?', answers: ['Giáo viên bình thường', 'Một nhân vật giải trí người lớn', 'Giáo viên dạy thể dục', 'Nhà khoa học'], correctIndex: 1 },
            { question: 'Nếu `grand_teacher.png` được tuyển vào trường, bạn nghĩ môn học nào sẽ khiến phụ huynh muốn họp khẩn?', answers: ['Toán học', 'Vật lý', 'Giáo dục giới tính', 'Lịch sử'], correctIndex: 2 }
        ]
    },
    {
        character: 'Yua Mikami',
        image: '../assets/images/characters/yua_mikami.png',
        questions: [
            { question: 'Yua Mikami là một cái tên nổi tiếng trong ngành giải trí người lớn. Cô được biết đến với vai trò nào?', answers: ['Ca sĩ', 'Diễn viên phim người lớn', 'Giáo viên', 'Nhà báo'], correctIndex: 1 },
            { question: 'Nếu Yua Mikami đổi nghề sang một công việc văn phòng bình thường, điều gì sẽ khiến đồng nghiệp bất ngờ nhất?', answers: ['Cô từng là idol và diễn viên phim người lớn', 'Cô từng là vận động viên', 'Cô từng là giáo viên', 'Cô từng là phi công'], correctIndex: 0 }
        ]
    },
    {
        character: 'My',
        image: '../assets/images/characters/my.png',
        questions: [
            { question: 'Nhân vật trong ảnh có tên là My. Bạn có nhận ra cô ấy là ai không?', answers: ['Mai', 'My', 'Minh', 'Mỵ'], correctIndex: 1 },
            { question: 'Nếu nhìn vào ảnh và filename `my.png`, tên của nhân vật này là gì?', answers: ['May', 'Mei', 'My', 'Mia'], correctIndex: 2 }
        ]
    },
    {
        character: '',
        image: '../assets/images/illness/gonorrhea.png',
        questions: [
            { question: '`gonorrhea` là loại khách không mời mà đến, đã đến còn để lại quà. Đây là bệnh gì?', answers: ['HIV', 'Giang mai', 'Bệnh lậu', 'Viêm gan'], correctIndex: 2 },
            { question: 'Nếu bệnh lậu có thể gửi lời nhắn, câu nào hợp nhất: “Xin chào”, “Tôi nhớ bạn”, hay “Chúng ta cần nói chuyện”?', answers: ['Xin chào', 'Tôi nhớ bạn', 'Chúng ta cần nói chuyện', 'Chúc ngủ ngon'], correctIndex: 2 }
        ]
    },
    {
        character: '',
        image: '../assets/images/illness/hiv.png',
        questions: [
            { question: 'HIV là viết tắt của cụm từ nào?', answers: ['Human Immunodeficiency Virus', 'Human Infection Virus', 'Human Immune Variation', 'Health Immunity Virus'], correctIndex: 0 },
            { question: 'HIV không phải thứ để đùa cợt ngoài đời. Vậy kiến thức nào giúp giảm nguy cơ lây truyền nó?', answers: ['Dùng chung kim tiêm', 'Quan hệ tình dục an toàn và không dùng chung kim tiêm', 'Không cần xét nghiệm', 'Chỉ uống vitamin'], correctIndex: 1 }
        ]
    },
    {
        character: '',
        image: '../assets/images/illness/siphillis.png',
        questions: [
            { question: '`siphillis` nhìn tên đã thấy giống một con boss trong game mà bạn tuyệt đối không muốn unlock. Nó là bệnh gì?', answers: ['Bệnh lậu', 'Giang mai', 'HIV', 'Viêm gan'], correctIndex: 1 },
            { question: 'Nếu giang mai có nút “Undo”, có lẽ nhân loại đã spam nút đó từ rất lâu. Bệnh này thuộc nhóm bệnh nào?', answers: ['Bệnh tim', 'Bệnh đường hô hấp', 'Bệnh lây truyền qua đường tình dục (STI)', 'Bệnh về mắt'], correctIndex: 2 }
        ]
    },
    {
        character: '',
        image: '../assets/images/position/cowgirl.png',
        questions: [
            { question: '`cowgirl` nghe như một nghề ở miền Tây nước Mỹ, nhưng trong game này lại là một tư thế nổi tiếng. Nó là gì?', answers: ['Một nghề nghiệp', 'Một tư thế quan hệ tình dục', 'Một loại thuốc', 'Một loại đồ chơi'], correctIndex: 1 },
            { question: 'Nếu đặt tên các tư thế quan hệ theo nghề nghiệp, `cowgirl` rõ ràng đã chọn đúng ngành có đồng phục tưởng tượng khá đặc biệt. Nó ám chỉ tư thế nào?', answers: ['Một người nằm trên và đối tác ở dưới', 'Hai người đứng', 'Hai người nằm cạnh nhau', 'Một người ngồi một mình'], correctIndex: 0 }
        ]
    },
    {
        character: '',
        image: '../assets/images/position/doggy.png',
        questions: [
            { question: '`doggy` nghe như tên một chú chó ngoan, nhưng trong ngữ cảnh người lớn thì nó chẳng liên quan gì đến việc dắt chó đi dạo. Đây là tư thế nào?', answers: ['Một giống chó', 'Một tư thế quan hệ tình dục', 'Một loại thuốc', 'Một trò chơi'], correctIndex: 1 },
            { question: 'Nếu ai đó nói “tối nay chơi doggy”, bạn nên chuẩn bị dây xích cho chó hay hiểu rằng họ đang nói chuyện người lớn?', answers: ['Dắt chó đi dạo', 'Chơi với thú cưng', 'Quan hệ theo tư thế doggy', 'Chơi game'], correctIndex: 2 }
        ]
    },
    {
        character: '',
        image: '../assets/images/position/missonary.png',
        questions: [
            { question: '`missionary` nghe giống người đi truyền giáo, nhưng trong phòng ngủ thì nghĩa lại khác hoàn toàn. Đây là tư thế nào?', answers: ['Một nghề', 'Một tư thế quan hệ tình dục', 'Một loại thuốc', 'Một tôn giáo'], correctIndex: 1 },
            { question: 'Nếu một nhà truyền giáo nghe thấy từ “missionary” trong cuộc trò chuyện này, họ có thể sẽ cần hỏi lại: “Khoan, chúng ta đang nói về cái gì?”', answers: ['Hai người đứng', 'Một người nằm trên người kia, thường mặt đối mặt', 'Hai người ngồi quay lưng', 'Một người đứng một mình'], correctIndex: 1 }
        ]
    },
    {
        character: '',
        image: '../assets/images/position/sixnine.png',
        questions: [
            { question: '`sixnine` là cái tên mà khi viết cạnh nhau tự nhiên trở nên đáng ngờ một cách không cần thiết. Nó ám chỉ điều gì?', answers: ['Một con số may mắn', 'Tư thế tình dục 69', 'Một loại thuốc', 'Một trò chơi'], correctIndex: 1 },
            { question: 'Nếu giáo viên toán hỏi “69 là gì?”, bạn có thể trả lời đúng toán học, nhưng tại sao cả lớp lại bắt đầu cười?', answers: ['Vì 69 là số nguyên tố', 'Vì 69 là số đẹp', 'Vì 69 cũng là tên một tư thế tình dục', 'Vì 69 là số lớn nhất'], correctIndex: 2 }
        ]
    },
    {
        character: '',
        image: '../assets/images/protection/condom.png',
        questions: [
            { question: '`condom` là món đồ nhỏ bé nhưng gánh trên vai một lượng trách nhiệm lớn hơn vẻ ngoài của nó. Nó dùng để làm gì?', answers: ['Tăng chiều cao', 'Phòng tránh thai và giảm nguy cơ lây nhiễm STI', 'Điều trị HIV', 'Tăng testosterone'], correctIndex: 1 },
            { question: 'Có những thứ càng rẻ càng không nên tiết kiệm. Bao cao su có phải một trong số đó không?', answers: ['Có', 'Không', 'Chỉ khi dùng ban ngày', 'Chỉ khi không có bệnh'], correctIndex: 1 }
        ]
    },
    {
        character: '',
        image: '../assets/images/protection/creampie.png',
        questions: [
            { question: '`creampie` nghe như món bánh ở tiệm dessert, nhưng chắc chắn không phải thứ bạn nên gọi ở quầy bánh. Trong ngữ cảnh người lớn, thuật ngữ này ám chỉ điều gì?', answers: ['Một loại bánh', 'Xuất tinh bên trong âm đạo hoặc hậu môn trong quan hệ tình dục', 'Một phương pháp tránh thai', 'Một loại bao cao su'], correctIndex: 1 },
            { question: 'Nếu nhìn thấy file `creampie.png` trong folder “protection”, bạn có nghĩ người đặt tên folder này đang rất lạc quan không?', answers: ['Folder được đặt tên hoàn toàn chính xác', 'Folder có vẻ đặt tên khá mâu thuẫn với nội dung', 'Đây chắc chắn là thuốc', 'Đây là một loại bao cao su'], correctIndex: 1 }
        ]
    },
    {
        character: '',
        image: '../assets/images/protection/cumout.png',
        questions: [
            { question: '`cumout` nghe như một khẩu hiệu thể thao rất đáng ngờ. Trong ngữ cảnh tình dục, nó liên quan đến phương pháp tránh thai nào?', answers: ['Bao cao su', 'Thuốc tránh thai', 'Xuất tinh ngoài (withdrawal)', 'Que cấy tránh thai'], correctIndex: 2 },
            { question: 'Có một phương pháp mà người ta nghĩ “chắc kịp”. Vấn đề là cơ thể con người không phải ứng dụng có nút Cancel. Đó là phương pháp nào?', answers: ['Bao cao su', 'Xuất tinh ngoài', 'Thuốc tránh thai', 'Triệt sản'], correctIndex: 1 }
        ]
    },
    {
        character: '',
        image: '../assets/images/sextoy/anal_toy.png',
        questions: [
            { question: '`anal_toy` nghe khá thẳng thắn, gần như không cho người đọc cơ hội giả vờ không hiểu. Nó thuộc nhóm đồ chơi nào?', answers: ['Đồ chơi cho trẻ em', 'Đồ chơi tình dục dùng cho hậu môn', 'Đồ chơi điện tử', 'Đồ chơi thể thao'], correctIndex: 1 },
            { question: 'Nếu một món đồ có chữ “anal” ngay trong tên file, bạn có cần mở Photoshop để đoán mục đích sử dụng nữa không?', answers: ['Liên quan đến hậu môn', 'Liên quan đến mắt', 'Liên quan đến tai', 'Liên quan đến chân'], correctIndex: 0 }
        ]
    },
    {
        character: '',
        image: '../assets/images/sextoy/egg_vibrator.png',
        questions: [
            { question: '`egg_vibrator` nghe như một quả trứng đã quyết định từ bỏ nghề làm bữa sáng. Đây là loại đồ chơi gì?', answers: ['Một quả trứng ăn được', 'Máy rung tình dục dạng trứng', 'Một loại thuốc', 'Một thiết bị nhà bếp'], correctIndex: 1 },
            { question: 'Nếu quả trứng này xuất hiện trong tủ lạnh, bạn có nên luộc nó không?', answers: ['Có', 'Không, đó là đồ chơi tình dục', 'Có, trong 10 phút', 'Chỉ luộc lòng đỏ'], correctIndex: 1 }
        ]
    },
    {
        character: '',
        image: '../assets/images/sextoy/fake_dick.png',
        questions: [
            { question: '`fake_dick` là một cái tên có độ vòng vo gần bằng số 0. Nó dùng để chỉ loại sản phẩm nào?', answers: ['Bao cao su', 'Dương vật giả / dildo', 'Máy massage', 'Thuốc'], correctIndex: 1 },
            { question: 'Nếu ai đó nói “đây không phải thật”, nhưng filename lại là `fake_dick.png`, Sherlock Holmes có cần xuất hiện không?', answers: ['Đây là một con vật', 'Đây là một loại thức ăn', 'Đây là dương vật giả', 'Đây là một loại thuốc'], correctIndex: 2 }
        ]
    },
    {
        character: '',
        image: '../assets/images/sextoy/fake_pussy.png',
        questions: [
            { question: '`fake_pussy` cũng thuộc trường phái đặt tên “nói thẳng cho đỡ mất thời gian”. Nó là sản phẩm gì?', answers: ['Một loại thuốc', 'Âm đạo giả / đồ chơi tình dục mô phỏng âm đạo', 'Một loại quần áo', 'Một loại bao cao su'], correctIndex: 1 },
            { question: 'Nếu filename đã nói hết đáp án, câu hỏi này có còn gọi là quiz không hay chỉ là bài kiểm tra khả năng đọc tiếng Anh?', answers: ['Một sản phẩm mô phỏng âm đạo', 'Một con mèo giả', 'Một loại thuốc', 'Một loại đồ ăn'], correctIndex: 0 }
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
