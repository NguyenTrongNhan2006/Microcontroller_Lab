# Lab 2: Timer Interrupt and LED Scanning

**Course:** Thực tập Vi điều khiển, HCMUT - BKU

**Instructor:** Dr. Le Trong Nhan

Source hoàn chỉnh của **10 exercise** theo tài liệu
`VXL_VDK_Lab_2_Timer.pdf` (trang 9-18), cho **STM32F103C6**.
Mỗi bài có file riêng `Source_Code/Src/exerciseN.c`; build chọn đúng một bài.

## Các bài đã cài đặt

| Bài | Hành vi | Nơi xử lý |
| --- | --- | --- |
| 1 | Hai LED 7 đoạn lần lượt hiển thị 1, 2; đổi mỗi 500 ms | TIM2 ISR |
| 2 | Quét 12:30 qua 4 LED, slot 500 ms; DOT đổi trạng thái mỗi giây | TIM2 ISR |
| 3 | `update7SEG(index)` dùng `led_buffer[4] = {1,2,3,4}` | TIM2 ISR |
| 4 | Slot 250 ms, đủ 4 LED trong 1 giây (frame 1 Hz) | TIM2 ISR |
| 5 | HH:MM bắt đầu 15:08:50; `updateClockBuffer()`, thêm số 0 phía trước | Quét/DOT trong ISR, clock dùng HAL_Delay trong main |
| 6 | Thêm timer phần mềm; LED PA5 đổi sau 1 giây, rồi mỗi 2 giây; clock cũng chạy không blocking | Timer/quét/DOT trong ISR; LED/clock trong main |
| 7 | Clock và DOT chuyển sang main bằng timer phần mềm | Chỉ quét còn trong ISR |
| 8 | Chuyển cả quét 7 đoạn sang main | ISR chỉ cập nhật software timers |
| 9 | `updateLEDMatrix(index)` quét 8 cột để hiển thị chữ A | main |
| 10 | Chữ A dịch vòng sang trái một cột mỗi 500 ms | main |

File HEX có sẵn: [Firmware](Firmware/), từ `exercise01.hex` đến
`exercise10.hex`. Xem [build và chọn bài](Source_Code/README.md),
[ghi chú bài tập](Docs/EXERCISE_NOTES.md) và
[kết quả kiểm tra](Source_Code/VERIFICATION.md).

## GPIO theo hình trong giáo trình

| Tín hiệu | Chân | Mức bật |
| --- | --- | --- |
| DOT (hai LED giữa) | PA4 | LOW |
| LED đỏ thử timer | PA5 | LOW |
| EN0..EN3, qua PNP chọn anode 7 đoạn | PA6..PA9 | LOW |
| Segment a..g | PB0..PB6 | LOW |
| ENM0, ENM1 | PA2, PA3 | LOW, theo mạch ULN/pull-up tham chiếu |
| ENM2..ENM7 | PA10..PA15 | LOW, theo mạch ULN/pull-up tham chiếu |
| ROW0..ROW7 | PB8..PB15 | LOW; bit 0 của buffer tương ứng ROW0 |

Mạch ma trận tham chiếu kéo các cột lên +3.3 V qua điện trở; ULN2803
kéo cột xuống khi đầu vào HIGH. Vì vậy đầu vào **LOW chọn cột** trong
bộ code này. Nếu mạch thực tế dùng ULN2803 để chọn cột cathode kiểu khác,
phải đổi cực tính/dây tương ứng trong `matrix.c`.
Code tắt tất cả digit/cột trước khi thay đổi dữ liệu chung để tránh ghosting.

## Timer

HSI = 8 MHz, APB1 divider = 1, TIM2 prescaler = 7999, ARR = 9.
Chu kỳ ngắt mặc định là `(7999+1)*(9+1)/8000000 = 10 ms`.
Bài 1-3 giữ các slot chậm theo yêu cầu, bài 4 dùng 250 ms.
Bài 5-10 dùng mặc định 250 ms cho 7 đoạn và 10 ms cho ma trận;
tốc độ này thuận tiện quan sát nhưng có thể thấy nhấp nháy.
Có cấu hình nhanh để build trong [Source_Code/README.md](Source_Code/README.md).

Đã kiểm thử logic và build ARM. Chưa xác nhận chạy mạch Proteus 8.17 hoặc
bo thật; lần cập nhật này cung cấp code/HEX, không có project Proteus mới.
