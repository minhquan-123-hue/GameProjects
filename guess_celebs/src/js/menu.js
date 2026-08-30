/**
 * menu.js
 * Xử lý tương tác menu chính của game
 * 
 * Chức năng:
 * - Lắng nghe sự kiện click nút "xuất"
 * - Điều hướng đến các màn hình khác
 */

document.addEventListener('DOMContentLoaded', function() {
    const btnStart = document.getElementById('btnStart');

    if (btnStart) {
        btnStart.addEventListener('click', function() {
            console.log('Nút xuất được click');
            // TODO: Chuyển đến màn hình tiếp theo (game play, hoặc selection screen)
            // Tạm thời hiển thị thông báo
            alert('Sắp bắt đầu game!');
        });
    }
});
