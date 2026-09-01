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
                question: 'Sinh ra ở vùng quê ngèo tại Tunisia Châu Phi, không để hoàn cảnh dập tắt ước mơ , năm lên 7 sục 10 lần ngày , 18 tuổi đụ bác hàng xóm 43 tuổi đang chửa bụng to, 2 năm ở Pháp quay tiktok sigma , giờ anh là top 2 male pornstar ở porhub nhờ tài bú bướm và địt như "bull" , nếu xem sex tây nhiều kiểu gì bạn cũng biết ?',
                answers: ['Gatut', 'Kamila benzo', 'Sibao otuzzo', 'Minh Quan'],
                correctIndex: 0
            },
            {
                question: 'Không hút thuốc, không rượu bia, không sugar, không chơi đồ , là câu anh phát biểu khi lên nhận giải diễn viên sex tự do của năm tại Los Agerles Mỹ, địt 1300 fans trong một năm một con số đến bố bạn của phải mở ước, anh ấy là ai?',
                answers: ['Kamlia Sahhot', 'Chekcutao DaiTo', 'DamDac himki', 'Gatut'],
                correctIndex: 3
            }
        ]
    },
    {
        character: 'Johnny Sins',
        image: '../assets/characters/johnny_sins_2.png',
        questions: [
            {
                question: 'Ước mơ trở thành người có nhiều "kinh nghiệm" nhất thể giới: anh đã trải qua nhiều công việc thợ vôi vữa , giao hàng bánh pizza , thợ sửa ống nước, sau đó chán công việc chân tay rồi anh có đi học làm bác sĩ phụ Khoa , và được nhận làm phi công lên Sảo nghiên cứu giao phối của sinh vật sao Hỏa? Đúng là một cuộc đời đang sống!',
                answers: ['Nguyễn Minh Khoa', 'Nguyễn Minh Triết', 'Đặng Thế Anh', 'Johnny Sins'],
                correctIndex: 3
            },
            {
                question: 'Người đàn ông hói đầu này đã phá trinh 2500 bà mẹ góa chồng , con hàng 19,5 cm chưa từng nghỉ ngơi trong 16 năm qua , Mỗi người "đi qua" đời anh đều có những kỷ niệm khó có thể diễn tả thành lời , người đàn ông là này là ai? ',
                answers: ['Nguyễn Minh Triết', 'Nguyễn Minh Khoa', 'Johnny Sins', 'Bế Nhật Trung Anh'],
                correctIndex: 2
            }
        ]
    },
    {
        character: 'Tokuda',
        image: '../assets/characters/tokuda_shigeo.png',
        questions: [
            {
                question: 'Bố ơi con vô sinh rồi , huhuhu lời của người con zai nói với bố sau khi đi khám nam khoa về, Bố thương con đành phải giúp đỡ 2 vợ chồng sớm sinh quý tử , sau gần một tháng vét máng con dâu, cuối cùng gia đình cũng có tin mừng. Người đàn ông nhân từ đó là ai ? ',
                answers: ['Misubi zama', 'Natsu betsu', 'Nobita netka', 'Tokuda Shigeo'],
                correctIndex: 3
            },
            {
                question: 'Giấu vợ con đóng "sẽ" gần 13 năm , nay đã 90 tuổi , hơn 600 bộ phim đã xuất lò , 936 nữ diễn viên thán phục sự "dai" của ông, bao nhiêu thanh niên già trẻ lớn bé đều ngưỡng mộ, nhưng citizờn không biết nay Huyền Thoại tung tích ra sao ?',
                answers: ['Suneo gike', 'Doraemon', 'Chaien', 'Tokuda'],
                correctIndex: 3
            }
        ]
    },
    {
        character: 'Owen Gray',
        image: '../assets/characters/owen_gray.png',
        questions: [
            {
                question: 'Là một thợ vôi vữa , anh nghĩ cả đời mình chẳng khấm khá lên được, thế mà tình thế đã xoay chuyển , hôm đó mẹ bạn anh đến chơi nhà anh chẳng có gì ngoài các tút mời bác ăn , 2 bác cháu đang ngon thì bạn nó vào ? nó hét lên....',
                answers: ['cái địt con mẹ', 'Owen cậu đang làm gì vậy?', 'oh mama...', 'nooooooo'],
                correctIndex: 1
            },
            {
                question: 'Đừng nhìn măt mà bắt hình dong , chỉ mới 18 tuổi , anh có gần như mọi thứ trong cuộc sống: tiền bạc , xe sang , rượu đắt , ma túy ngon, vậy mà anh vẫn thấy không thỏa mãn với đời mình anh ấy làm nghề gì ?',
                answers: ['Thầy phong thủy', 'Bartender', 'diễn viễn pỏn', 'giáo viên cấp 3'],
                correctIndex: 2
            }
        ]
    },
    {
        character: 'Danny D',
        image: '../assets/characters/danny_D.png',
        questions: [
            {
                question: 'Với tinh thần quyết thắng , anh chỉ nhần thấy mục tiêu của mình , các bà mẹ đơn thân , những bé học sinh cấp 3 mới nhú , không có ai là anh không chiều được , 23 cm một trong những chiếc gậy bự nhất trong ngành ?',
                answers: ['Dan Hooker', 'Connor Macdonald', 'Danny D', 'Kan Funkai'],
                correctIndex: 2
            },
            {
                question: 'Hồi mới biết đập lọ ,tôi thường xem sex Nhật , lúc đó xem thấy thích lắm mà dần dần thấy lông lông , tôi lại thấy ghê , qua Kênh địt nhau mỹ tự dưng thấy cây gậy của anh này bự mà em diễn viên hói bên dưới là tôi khoái lắm , cũng mới được 12 năm xem sex thôi, các con vợ biết anh này không ?',
                answers: ['Danny D', 'KanFun Sekki', 'Dezel Wasshigton', 'Nekork Citai'],
                correctIndex: 0
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
