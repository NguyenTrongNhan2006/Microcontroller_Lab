# Ghi chú Exercise và Report Lab 2

Theo VXL_VDK_Lab_2_Timer.pdf, phần Timer Interrupt and LED Scanning.
Các link dưới đây trỏ tới phần source có thể dùng để giải thích trong báo cáo.

- Bài 1: [exercise1.c](../Source_Code/Src/exercise1.c). Slot 500 ms cho hai
  digit: một frame 1 giây, tần số quét toàn màn hình = **1 Hz**.
- Bài 2: [exercise2.c](../Source_Code/Src/exercise2.c). Bốn slot 500 ms:
  frame 2 giây, **0.5 Hz**. DOT đổi trạng thái mỗi 1 giây,
  nên chu kỳ sáng-tắt hoàn chỉnh là 2 giây.
- Bài 3: [display.c](../Source_Code/Src/display.c), hàm `update7SEG()`.
  Index hợp lệ 0..3; tắt cả bốn anode trước khi đổi segment rồi chọn một digit.
- Bài 4: [exercise4.c](../Source_Code/Src/exercise4.c). Slot = 250 ms:
  frame = 4 * 250 = 1000 ms, **1 Hz**.
- Bài 5: [clock.c](../Source_Code/Src/clock.c), `updateClockBuffer()`.
  Bốn digit hiển thị HH:MM: `hour/10, hour%10, minute/10, minute%10`.
  Hình minh họa có hai digit cho giờ và hai digit cho phút.
- Bài 6: [software_timer.c](../Source_Code/Src/software_timer.c).
  Nếu bỏ `setTimer0(1000)`, counter và flag ban đầu = 0 nên LED không đổi.
  Với `setTimer0(1)`, chia nguyên 1/10 = 0 nên timer không chạy, flag không lên.
  Với `setTimer0(10)`, counter = 1, ngắt tiếp theo sau 10 ms đặt flag;
  lần sau `setTimer0(2000)` tạo khoảng 2 giây. Khởi tạo đầy đủ ở
  [exercise6.c](../Source_Code/Src/exercise6.c).
- Bài 7: [exercise7.c](../Source_Code/Src/exercise7.c): main nhận sự kiện
  giây rồi cập nhật clock và DOT, không chờ HAL_Delay.
- Bài 8: [exercise8.c](../Source_Code/Src/exercise8.c) và
  [services.c](../Source_Code/Src/services.c): cả quét digit chuyển sang main,
  ISR chỉ chạy `timer_run()`.
- Bài 9: [matrix.c](../Source_Code/Src/matrix.c), `updateLEDMatrix()`.
  Bit 0 của mỗi cột tương ứng ROW0; chữ A có các hàng
  `18 24 42 42 7E 42 42 00` (hex). Slot 10 ms cho 8 cột tạo frame 80 ms,
  **12.5 Hz**; nên dùng profile nhanh khi cần nhìn ổn định.
- Bài 10: [exercise10.c](../Source_Code/Src/exercise10.c).
  Mỗi 500 ms dịch buffer cột sang trái và đưa cột đầu xuống cuối.
  Timer scan và timer animation độc lập; đủ 8 bước khôi phục hình ban đầu.

Báo cáo yêu cầu ảnh mạch cần chụp từ project Proteus thực tế.
Source/HEX này chưa cung cấp ảnh hoặc project mô phỏng đã kiểm chứng.
