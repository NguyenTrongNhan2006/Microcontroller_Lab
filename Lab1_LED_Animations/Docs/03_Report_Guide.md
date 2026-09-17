# Hướng Dẫn Trình Bày Báo Cáo Lab 1 (Report 1 & Report 2)

Theo yêu cầu của Thầy trong mục **4. Exercise and Report**, mỗi bài tập sinh viên cần nộp báo cáo gồm 2 phần:

---

## 1. Report 1: Sơ đồ nguyên lý Proteus (Schematic)
- **Yêu cầu**: Chụp ảnh màn hình rõ nét sơ đồ mạch mô phỏng Proteus của bài tập đó.
- **Quy cách**:
  - Hình ảnh cần chụp đầy đủ: Chip vi điều khiển STM32F103C6, hệ thống LED / LED 7 đoạn, kết nối nguồn 3.3V, VDDA, VSSA.
  - Lưu ảnh vào thư mục `Proteus/schematics/` với tên tương ứng (ví dụ: `ex1_schematic.png`, `ex2_schematic.png`...).
  - Dưới mỗi hình chụp trong báo cáo, ghi caption kèm link tải file Proteus dự án (dẫn trực tiếp đến link GitHub của bạn).

## 2. Report 2: Trình bày mã nguồn (Source Code)
- **Yêu cầu**: Trình bày mã nguồn nằm trong vòng lặp vô hạn `while (1)` của dự án, và các hàm con tự định nghĩa (User-defined functions).
- **Quy cách**:
  - Mã nguồn phải có chú thích (comments) giải thích thuật toán, giải thuật chuyển đổi trạng thái FSM hoặc giải mã LED 7 đoạn.
  - Trình bày gọn gàng, định dạng code block chuẩn C.

---

## Bảng Tổng Hợp Yêu Cầu Từng Exercise:

| Bài tập | Mô tả chức năng | Report 1 (Schematic) | Report 2 (Mã nguồn) |
|---|---|---|---|
| **Exercise 1** | Đảo trạng thái 2 LED mỗi 2s (PA5, PA6) | `ex1_schematic.png` | Code trong `while(1)` |
| **Exercise 2** | Đèn giao thông đơn (PA5 Đỏ 5s, PA7 Xanh 3s, PA6 Vàng 2s) | `ex2_schematic.png` | Code trong `while(1)` |
| **Exercise 3** | Đèn giao thông 4 ngã (12 LED) | `ex3_schematic.png` | Code trong `while(1)` |
| **Exercise 4** | LED 7 đoạn Anode chung (PB0..PB6) | `ex4_schematic.png` | Code hàm `display7SEG(int num)` |
| **Exercise 5** | Đèn giao thông 4 ngã đếm ngược LED 7 đoạn | `ex5_schematic.png` | Code đồng bộ trong `while(1)` |
| **Exercise 6** | Đồng hồ 12 LED (PA4..PA15): Test tuần tự | `ex6_schematic.png` | Code test tuần tự |
| **Exercise 7** | Hàm tắt toàn bộ 12 LED đồng hồ | Dùng chung sơ đồ Ex 6 | Code hàm `clearAllClock()` |
| **Exercise 8** | Hàm bật LED tại vị trí `num` (0..11) | Dùng chung sơ đồ Ex 6 | Code hàm `setNumberOnClock(int num)` |
| **Exercise 9** | Hàm tắt LED tại vị trí `num` (0..11) | Dùng chung sơ đồ Ex 6 | Code hàm `clearNumberOnClock(int num)` |
| **Exercise 10**| Đồng hồ kim 12 LED (Giờ, Phút, Giây - max 3 LED sáng) | `ex10_schematic.png` | Code thuật toán đồng hồ kim |
