# Kết quả kiểm tra Lab 2

Ngày kiểm tra: 2026-09-28. Target STM32F103C6, HSI 8 MHz.
Profile mặc định: TIM2 tick 10 ms, quét 7 đoạn bài 5-10 slot 250 ms,
ma trận slot 10 ms.

## Đã kiểm chứng

- GCC host compile với `-Wall -Wextra -Werror`: đủ 10 exercise PASS.
- Chuyển digit đúng biên 500 ms (bài 1-3) và 250 ms (bài 4-10),
  đúng một digit/cột được chọn tại một thời điểm: PASS.
- DOT đổi mỗi giây; LED thử timer bài 6 đổi sau 1 giây rồi mỗi 2 giây: PASS.
- Mẫu segment 0-9, thêm 0 cho HH:MM, chuyển 23:59:59 -> 00:00:00: PASS.
- Clock nhận đủ số giây sau khi main bận 5 giây, không mất sự kiện: PASS.
- Buffer chữ A, 8 cột, bit ROW0 trên cùng, dịch trái và quay vòng: PASS.
- Timeout timer mẫu không khởi tạo / 1 ms / 10 ms / 1000 ms; timer định kỳ
  làm tròn lên; id/giá trị digit ngoài phạm vi; bảo toàn IRQ mask: PASS.
- Tắt các enable trước khi đổi data; bảo toàn bit GPIO ngoài nhóm: PASS.
- Bài 8-10 không ghi GPIO trong callback ISR, không gọi HAL_Delay;
  callback bỏ qua instance timer khác TIM2: PASS.
- ARM GNU 14.3.1 + STM32CubeF1 V1.8.7: build đủ 10 ELF/HEX thành công.
- Intel HEX: checksum tất cả record, giới hạn Flash 32 KB, địa chỉ stack,
  vector Reset và vector TIM2 hợp lệ: PASS.

| Bài | text (byte) | data (byte) | bss + vùng dự trữ (byte) |
| --- | ---: | ---: | ---: |
| 1 | 3928 | 36 | 1196 |
| 2 | 3932 | 36 | 1196 |
| 3 | 3932 | 36 | 1196 |
| 4 | 3928 | 36 | 1196 |
| 5 | 4168 | 48 | 1200 |
| 6 | 4448 | 48 | 1200 |
| 7 | 4368 | 48 | 1200 |
| 8 | 4320 | 48 | 1192 |
| 9 | 4636 | 48 | 1200 |
| 10 | 4716 | 48 | 1200 |

Tất cả bản build nằm trong giới hạn Flash 32 KB và RAM 10 KB.

## Phạm vi

Host tests chạy source thật với HAL/GPIO và ngắt giả lập; chúng kiểm tra
logic và thứ tự thao tác, không đo điện hoặc độ chính xác thời gian MCU.
Chưa chạy kiểm chứng mạch Proteus 8.17 hay bo thật. Profile nhanh được
hướng dẫn trong README, các kết quả ở đây áp dụng cho profile mặc định.
Linker còn cảnh báo các syscall newlib/nosys `_close`, `_lseek`, `_read`,
`_write` chưa được cài đặt; firmware không dùng file I/O/printf trên MCU.
Không tuyên bố linker hoàn toàn sạch cảnh báo.
