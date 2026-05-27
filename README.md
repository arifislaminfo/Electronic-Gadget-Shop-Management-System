# Electronic-Gadget-Shop-Management-System
A 'C-language' shop management system built for 1st year level CSE Students 




<div align="center">

# 🛍️ Electronic Gadget Shop Management System

<img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=22&pause=1000&color=2563EB&center=true&vCenter=true&width=600&lines=Built+with+C+Programming+Language;Console-Based+Shop+Management;Login+%7C+CRUD+%7C+Billing+%7C+Discounts;CSE115L+Project+%7C+North+South+University" alt="Typing SVG" />

<br/>

![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![IDE](https://img.shields.io/badge/IDE-Code%3A%3ABlocks-orange?style=for-the-badge)
![Course](https://img.shields.io/badge/Course-CSE115L-green?style=for-the-badge)
![University](https://img.shields.io/badge/University-NSU-red?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge)

<br/>

> *A fully functional console-based shop management system that lets a gadget shop owner manage inventory, search products, generate invoices, and apply automatic discounts — all written in pure C.*

</div>

---

## 📌 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Demo](#-demo)
- [Project Structure](#-project-structure)
- [How It Works](#-how-it-works)
- [Getting Started](#-getting-started)
- [Login Credentials](#-login-credentials)
- [Discount Logic](#-discount-logic)
- [C Concepts Used](#-c-concepts-used)
- [Authors](#-authors)

---

## 🎯 About the Project

This project was built as part of the **CSE115L Laboratory Course** at **North South University**. It is a console-based **Electronic Gadget Shop Management System** written entirely in the **C programming language**.

The system allows a shop owner to:
- Securely log in to the system
- Add, view, search, edit, and delete products
- Generate customer invoices with automatic discounts
- Store all data permanently in a text file

---

## ✨ Features

| Feature | Description |
|---|---|
| 🔐 **Login System** | Secure login with username & password. 3 attempts allowed |
| 👁️ **View Products** | Display all products in a clean formatted table |
| ➕ **Add Product** | Add new products with auto-assigned unique ID |
| 🔍 **Search Product** | Case-insensitive partial search by name or brand |
| ✏️ **Edit Product** | Update any field — press ENTER to keep old value |
| 🗑️ **Delete Product** | Search, confirm, and remove a product safely |
| 🧾 **Generate Bill** | Multi-item invoice with automatic discount tiers |
| 💾 **File Storage** | Real-time save to `products.txt` after every action |

---

## 🎬 Demo

```
  =============================================
   ELECTRONIC GADGET SHOP MANAGEMENT SYSTEM
  =============================================
              ** USER LOGIN **

  Username: admin
  Password: ****

  Login successful! Welcome, Admin!

  =============================================
   ELECTRONIC GADGET SHOP MANAGEMENT SYSTEM
  =============================================
   Total Products in Stock: 5
  ---------------------------------------------
   1. View All Products
   2. Add New Product
   3. Search Product
   4. Edit Product
   5. Delete Product
   6. Generate Bill
   0. Exit
  ---------------------------------------------
  Enter your choice: _
```

```
  ========== ALL PRODUCTS ==========

  ID    Name                 Category        Brand           Price(BDT)  Stock
  -----------------------------------------------------------------------
  1     Samsung Galaxy S24   Phone           Samsung         85000.00   10
  2     Sony WH-1000XM5      Audio           Sony            35000.00   5
  3     Logitech MX Master   Computer        Logitech        12000.00   8
  4     iPhone 15            Phone           Apple           130000.00  5
  5     JBL Flip 6           Audio           JBL             8500.00    15
  -----------------------------------------------------------------------
  Total: 5 product(s)
```

```
  =============================================
        ELECTRONIC GADGET SHOP
             --- INVOICE ---
  =============================================
  Customer: Rahim Ahmed
  ---------------------------------------------
  Product              Qty    Price      Subtotal
  ---------------------------------------------
  Samsung Galaxy S24   1      85000.00   85000.00
  Sony WH-1000XM5      1      35000.00   35000.00
  ---------------------------------------------
  Total Amount   : BDT 120000.00
  Discount (15%) : BDT -18000.00
  Final Amount   : BDT 102000.00
  =============================================
       Thank you for shopping with us!
  =============================================
```

---

## 📁 Project Structure

```
Electronic-Gadget-Shop-Management-System/
│
├── 📄 gadget_shop.c        ← Main source code (all functions)
├── 📄 products.txt         ← Auto-generated data file (created on first run)
└── 📄 README.md            ← You are here!
```

---

## ⚙️ How It Works

```
Program Starts
      │
      ▼
┌─────────────┐
│ Login Check │ ──── Wrong 3 times ──── Program Exits
└─────────────┘
      │ Success
      ▼
┌──────────────────┐
│ Load products.txt│  ← Restores all previous data into memory
└──────────────────┘
      │
      ▼
┌─────────────────────────────────┐
│           MAIN MENU             │
│  1-View  2-Add  3-Search        │
│  4-Edit  5-Delete  6-Bill  0-Exit│
└─────────────────────────────────┘
      │
      ▼
  User picks option
      │
      ▼
Function runs → saveToFile() → Menu appears again
      │
      ▼
User presses 0 → Program exits safely
```

---

## 🚀 Getting Started

### Prerequisites
- **Code::Blocks** with MinGW compiler (recommended)
- OR any C compiler (GCC)

### Run with Code::Blocks
```
1. Download and install Code::Blocks with MinGW
2. Open Code::Blocks → File → New → Project → Console Application → C
3. Replace main.c content with gadget_shop.c code
4. Press F9 to Build and Run
```

### Run with GCC (Command Line)
```bash
gcc gadget_shop.c -o gadget_shop
./gadget_shop
```

### Run with VS Code
```bash
# Install C/C++ extension first, then:
gcc gadget_shop.c -o gadget_shop
./gadget_shop
```

---

## 🔑 Login Credentials

| Field | Value |
|---|---|
| **Username** | `admin` |
| **Password** | `1234` |
| **Max Attempts** | 3 |

> ⚠️ After 3 wrong attempts the program exits automatically.

---

## 💰 Discount Logic

The billing system automatically applies discounts based on total purchase:

```
Total Purchase          Discount Applied
──────────────────────────────────────────
Below 10,000 BDT   →   No discount  (0%)
10,000+ BDT        →   5% discount
20,000+ BDT        →   10% discount
50,000+ BDT        →   15% discount  ⭐ Best deal!
```

---

## 📚 C Concepts Used

```c
✅ struct          → struct Product groups all product fields
✅ array           → products[100] stores up to 100 products
✅ strings         → char arrays for name, category, brand
✅ file I/O        → fopen, fprintf, fscanf, fclose
✅ functions       → modular design — one function per feature
✅ pointers        → FILE *fp, char *str parameters
✅ loops           → for (view/search), while (login/billing), do-while (menu)
✅ conditionals    → if-else (discount), switch-case (menu)
✅ string functions → strcmp, strstr, strcpy, strlen, strcspn, tolower
```

---

## 👨‍💻 Authors

<table>
  <tr>
    <td align="center">
      <b>Ariful Islam</b><br/>
      <sub>ID: 2222651643</sub><br/>
      <sub>North South University</sub>
    </td>
    <td align="center">
      <b>Arpita Raha</b><br/>
      <sub>ID: 2232073643</sub><br/>
      <sub>North South University</sub>
    </td>
  </tr>
</table>

**Supervised by:** Dr. Chowdhury Farhan Ahmed
**Department:** Electrical and Computer Science Engineering
**Course:** CSE115L — Programming Language Lab
**University:** North South University, Dhaka, Bangladesh

---

<div align="center">

**⭐ If you found this helpful, please give it a star! ⭐**

![C](https://img.shields.io/badge/Made%20with-C-blue?style=flat-square&logo=c)


</div>