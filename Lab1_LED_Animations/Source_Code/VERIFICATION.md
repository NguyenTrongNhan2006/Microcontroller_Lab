# Kết quả kiểm tra Exercise 1–10

Kiểm tra ngày 2026-09-22.

## Đã chạy

- Host GCC: `Tests/test.ps1`, compile với `-Wall -Wextra -Werror`: PASS.
- Exercise 1–9: 120 trạng thái tại điểm HAL_Delay cho mỗi bài: PASS.
- Exercise 10: 43.201 trạng thái giây, từ 10:58:00 qua toàn bộ vòng 12 giờ:
  PASS (bao gồm chuyển phút, giờ, 11:59:59 → 00:00:00 và kim trùng nhau).
- Mask 7 đoạn 0–9, đầu vào ngoài phạm vi, bật/tắt 12 vị trí và bảo toàn
  các bit GPIO không liên quan: PASS.
- ARM GNU 14.3.1 + STM32CubeF1 V1.8.7: build và chuyển Intel HEX thành công
  cho đủ 10 bài bằng `build.ps1`.

| Bài | text (byte) | data (byte) | bss + vùng dự trữ (byte) |
| --- | ---: | ---: | ---: |
| 1 | 2908 | 20 | 1060 |
| 2 | 2920 | 20 | 1060 |
| 3 | 2948 | 20 | 1060 |
| 4 | 2912 | 20 | 1060 |
| 5 | 2976 | 20 | 1060 |
| 6 | 2896 | 20 | 1060 |
| 7 | 2856 | 20 | 1060 |
| 8 | 2892 | 20 | 1060 |
| 9 | 2912 | 20 | 1060 |
| 10 | 2948 | 20 | 1060 |

Các bản build nằm trong giới hạn Flash 32 KB / RAM 10 KB của STM32F103C6.

## Cảnh báo và giới hạn

- Linker báo `_close`, `_lseek`, `_read`, `_write` từ newlib/nosys chưa được
  cài đặt. Các bài không dùng file I/O hay printf trên MCU. Đây không phải
  firmware có giao tiếp terminal/UART; muốn thêm I/O phải retarget syscall.
- Linker cũng báo LOAD segment ELF có quyền RWX với linker script tối giản.
  Không tuyên bố build sạch hoàn toàn cảnh báo. File HEX không chứa quyền ELF.
- Host test thay HAL bằng mô hình GPIO và thời gian logic; không kiểm tra
  ngắt SysTick thực tế, độ chính xác HSI, dòng LED, đường dây hoặc model MCU.
- Chưa xác nhận chạy đủ 10 bài trong Proteus 8.17 hoặc trên bo thật.
  Không kèm project Proteus đang vẽ dở vào lần push code này.
- Mapping nguồn chính xác nằm ở `README.md` trong thư mục này; ảnh mạch
  có sẵn trong repo cần được đối chiếu pin trước khi dùng.
