# Thư Mục Mô Phỏng Proteus & Ảnh Sơ Đồ Mạch (Schematics)

Thư mục này dùng để lưu trữ file thiết kế mô phỏng **Proteus 8.10 SP0 Professional** (`.pdsprj`) và các hình ảnh chụp sơ đồ mạch nguyên lý của từng bài tập để phục vụ cho **Report 1**.

---

## 📁 Cấu Trúc Thư Mục
```
Proteus/
├── README.md               # Hướng dẫn này
├── STM32_Lab1.pdsprj       # File thiết kế mô phỏng Proteus của bạn (lưu vào đây)
└── schematics/             # Thư mục chứa ảnh chụp sơ đồ mạch từng bài tập
    ├── ex1_schematic.png   # Sơ đồ Exercise 1 (2 LED PA5, PA6)
    ├── ex2_schematic.png   # Sơ đồ Exercise 2 (Đèn giao thông đơn PA5, PA6, PA7)
    ├── ex3_schematic.png   # Sơ đồ Exercise 3 (Đèn giao thông 4 ngã 12 LED)
    ├── ex4_schematic.png   # Sơ đồ Exercise 4 (LED 7 đoạn PB0..PB6)
    ├── ex5_schematic.png   # Sơ đồ Exercise 5 (Đèn giao thông + LED 7 đoạn)
    ├── ex6_schematic.png   # Sơ đồ Exercise 6 (Đồng hồ 12 LED PA4..PA15)
    └── ex10_schematic.png  # Sơ đồ Exercise 10 (Đồng hồ kim hoàn chỉnh)
```

---

## 🖼️ Cách Thay Thế Ảnh Chụp Sơ Đồ Thực Tế
Hiện tại trong thư mục `schematics/` đã có sẵn các file placeholder mẫu. Sau khi bạn vẽ mạch trên Proteus:
1. Mở sơ đồ trên Proteus, nhấn phím `PrintScreen` (hoặc dùng `Snipping Tool` / `Win + Shift + S`) để chụp vùng mạch nguyên lý rõ nét.
2. Lưu/ghi đè file ảnh vào thư mục `schematics/` với đúng tên file (ví dụ `ex1_schematic.png`).
3. Khi bạn push lên GitHub, hình ảnh sơ đồ thực tế của bạn sẽ tự động hiển thị trong `README.md` của Lab 1 và trong các tài liệu báo cáo!
