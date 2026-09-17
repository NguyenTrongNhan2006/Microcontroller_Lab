# Hướng Dẫn Mô Phỏng Mạch STM32 Trên Proteus 8.10 SP0

Dựa theo Chapter 1, Mục 3: **Simulation on Proteus** trong giáo trình Vi điều khiển.

---

## 1. Khởi Động Proteus
> **Quan trọng**: Luôn mở Proteus bằng quyền **Run as Administrator** (Chuột phải vào biểu tượng Proteus -> Chọn `Run as administrator`). Nếu không chạy quyền admin, Proteus có thể báo lỗi không tìm thấy thư viện linh kiện (`No library found`).

## 2. Tạo Schematic Mới
1. Vào `File` -> `New Project`.
2. Đặt tên file (ví dụ `STM32_Lab1.pdsprj`) và chọn thư mục lưu (khuyến nghị lưu vào thư mục `Proteus/` trong repo).
3. Chọn **From Development Board: New Project** -> Chọn default schematic template.
4. Nhấn **Next** qua các bước tiếp theo và nhấn **Finish**.

## 3. Lấy Linh Kiện Ra Màn Hình
Nhấn phím tắt `P` (hoặc chuột phải -> `Place` -> `Component` -> `From Libraries`):
- `STM32F103C6`: Vi điều khiển ARM Cortex-M3.
- `LED-RED`: LED màu đỏ mô phỏng.
- `LED-YELLOW`: LED màu vàng mô phỏng.
- `LED-GREEN`: LED màu xanh lá mô phỏng.
- `7SEG-COM-ANODE`: LED 7 đoạn cực dương chung (Common Anode).
- `RES`: Điện trở hạn dòng (chọn giá trị 220Ω hoặc 330Ω).

## 4. Quy Tắc Nối Dây (Wiring Circuit)
1. **Đấu nối LED đơn (Active LOW)**:
   - Cực âm của LED (Cathode - phía vạch ngang) nối vào chân GPIO của STM32 (VD: `PA5`, `PA6`, `PA7`).
   - Cực dương của LED (Anode - phía đáy tam giác) nối vào nguồn `+3.3V`.
   - Khi chân STM32 xuất mức `0` (0V): Điện thế chênh lệch 3.3V - 0V = 3.3V -> LED SÁNG.
   - Khi chân STM32 xuất mức `1` (3.3V): Điện thế chênh lệch 3.3V - 3.3V = 0V -> LED TẮT.

2. **Cấp nguồn cho STM32 (BẮT BUỘC THEO BƯỚC 8 TRONG LAB MANUAL)**:
   - Lấy `POWER` terminal và `GROUND` terminal (`Place` -> `Terminal` -> `POWER` / `GROUND`).
   - Đặt nguồn `+3.3V`: Nhấp đúp vào terminal Power, gõ vào ô String: `+3.3V`.
   - **Gắn nhãn nguồn tham chiếu VDDA và VSSA**:
     - Vẽ 1 đoạn dây ngắn từ chân nguồn, chuột phải chọn `Place wire Label` -> Đặt nhãn `VDDA`.
     - Vẽ 1 đoạn dây ngắn từ mass, chuột phải chọn `Place wire Label` -> Đặt nhãn `VSSA`.
     - Chân `VDDA` nối đến `+3.3V`, chân `VSSA` nối đến `GND`. Nếu thiếu bước này, STM32 mô phỏng sẽ báo lỗi nguồn hoặc không chạy!

3. **Đấu nối LED 7 đoạn Anode chung (7SEG-COM-ANODE)**:
   - Chân chung (Common pin ở trên hoặc dưới) nối vào nguồn `+3.3V`.
   - Các chân tín hiệu từ `a`, `b`, `c`, `d`, `e`, `f`, `g` lần lượt nối vào `PB0`, `PB1`, `PB2`, `PB3`, `PB4`, `PB5`, `PB6`.
   - Mức logic `0` làm sáng thanh led tương ứng; mức `1` làm tắt.

## 5. Nạp File HEX Vào STM32 Trên Proteus
1. Nhấp đúp chuột trái vào chip **STM32F103C6** trên bản vẽ schematic.
2. Tại ô **Program File**, click vào biểu tượng thư mục màu vàng và duyệt đến file `.hex` được sinh ra từ STM32CubeIDE (nằm ở `Debug/xxx.hex`).
3. Ô **Crystal Frequency**: Giữ mặc định hoặc điền `8MHz`.
4. Nhấn **OK**.

## 6. Chạy Mô Phỏng & Gỡ Lỗi
- Nhấn nút **Play (Run Simulation)** ở góc dưới cùng bên trái màn hình Proteus (hoặc nhấn `F12`).
- Quan sát hoạt động chuyển màu của các LED.
- Để dừng mô phỏng: Nhấn nút **Stop** ở góc dưới cùng bên trái (hoặc menu `Debug` -> `Stop VMS Debugging`).
- *Chú ý*: Phải **Stop** mô phỏng trước khi biên dịch lại code bên CubeIDE, nếu không file hex sẽ bị khóa ghi.
