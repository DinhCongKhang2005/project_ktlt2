# project_ktlt2
Dự án quản lý sách ở thư viện:Cập nhật các thông tin sách: tên sách, tác giả, thể loại, mã sách(băm ra = code), số lượng mỗi loại, tình trạng(mượn, hết, còn,...).Quản lý thành viên : mã mượn sách,  thẻ mượn sách(cccd), ...Xử lý mượn trả sách, tìm kiếm (cây + bảng băm) theo tiêu đề , mã sách, tác giả,. thể loại,...); liệt kê sách quá hạn.Còn nhiều vấn đề khác cần quan tâm ...
#MÃ NGUỒN
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOOKS 100
#define MAX_READERS 50
#define MAX_BORROW 100

// Cấu trúc cho sách
struct Book {
    char id[10];
    char title[50];
    char author[50];
    char genre[30];
    int quantity;
    char status[20];
};

// Cấu trúc cho bạn đọc
struct Reader {
    char name[50];
    char student_id[10];
};

// Cấu trúc cho mượn sách
struct Borrow {
    char student_id[10];
    char book_id[10];
    char borrow_date[11];
    char due_date[11];
    int returned; // 0: chưa trả, 1: đã trả
};

struct Book books[MAX_BOOKS];
struct Reader readers[MAX_READERS];
struct Borrow borrows[MAX_BORROW];
int book_count = 0, reader_count = 0, borrow_count = 0;

// Hàm thêm sách
void add_book() {
    if (book_count >= MAX_BOOKS) {
        printf("Thu vien da day, khong the them sach!\n");
        return;
    }
    struct Book new_book;
    printf("Nhap ma sach: ");
    scanf("%s", new_book.id);
    getchar();
    printf("Nhap ten sach: ");
    fgets(new_book.title, 50, stdin);
    new_book.title[strcspn(new_book.title, "\n")] = 0;
    printf("Nhap tac gia: ");
    fgets(new_book.author, 50, stdin);
    new_book.author[strcspn(new_book.author, "\n")] = 0;
    printf("Nhap the loai: ");
    fgets(new_book.genre, 30, stdin);
    new_book.genre[strcspn(new_book.genre, "\n")] = 0;
    printf("Nhap so luong: ");
    scanf("%d", &new_book.quantity);
    printf("Nhap tinh trang (con/het): ");
    scanf("%s", new_book.status);

    books[book_count++] = new_book;
    printf("Them sach thanh cong!\n");
}

// Hàm thêm bạn đọc
void add_reader() {
    if (reader_count >= MAX_READERS) {
        printf("Danh sach ban doc da day!\n");
        return;
    }
    struct Reader new_reader;
    printf("Nhap ten ban doc: ");
    getchar();
    fgets(new_reader.name, 50, stdin);
    new_reader.name[strcspn(new_reader.name, "\n")] = 0;
    printf("Nhap ma sinh vien: ");
    scanf("%s", new_reader.student_id);

    readers[reader_count++] = new_reader;
    printf("Them ban doc thanh cong!\n");
}

// Hàm mượn sách
void borrow_book() {
    if (borrow_count >= MAX_BORROW) {
        printf("Danh sach muon sach da day!\n");
        return;
    }
    struct Borrow new_borrow;
    printf("Nhap ma sinh vien: ");
    scanf("%s", new_borrow.student_id);
    printf("Nhap ma sach: ");
    scanf("%s", new_borrow.book_id);
    printf("Nhap ngay muon (dd/mm/yyyy): ");
    scanf("%s", new_borrow.borrow_date);
    printf("Nhap ngay het han (dd/mm/yyyy): ");
    scanf("%s", new_borrow.due_date);
    new_borrow.returned = 0;

    // Kiểm tra sách có sẵn không
    for (int i = 0; i < book_count; i++) {
        if (strcmp(books[i].id, new_borrow.book_id) == 0) {
            if (books[i].quantity > 0 && strcmp(books[i].status, "con") == 0) {
                books[i].quantity--;
                if (books[i].quantity == 0) strcpy(books[i].status, "het");
                borrows[borrow_count++] = new_borrow;
                printf("Muon sach thanh cong!\n");
                return;
            }
        }
    }
    printf("Sach khong co san hoac da het!\n");
}

// Hàm trả sách
void return_book() {
    char student_id[10], book_id[10];
    printf("Nhap ma sinh vien: ");
    scanf("%s", student_id);
    printf("Nhap ma sach: ");
    scanf("%s", book_id);

    for (int i = 0; i < borrow_count; i++) {
        if (strcmp(borrows[i].student_id, student_id) == 0 && strcmp(borrows[i].book_id, book_id) == 0 && borrows[i].returned == 0) {
            borrows[i].returned = 1;
            for (int j = 0; j < book_count; j++) {
                if (strcmp(books[j].id, book_id) == 0) {
                    books[j].quantity++;
                    strcpy(books[j].status, "con");
                    break;
                }
            }
            printf("Tra sach thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay thong tin muon sach!\n");
}

// Hàm tìm kiếm sách
void search_book() {
    char keyword[50];
    printf("Nhap tu khoa (ten sach/tac gia/the loai): ");
    getchar();
    fgets(keyword, 50, stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < book_count; i++) {
        if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword) || strstr(books[i].genre, keyword)) {
            printf("Ma sach: %s, Ten sach: %s, Tac gia: %s, The loai: %s, So luong: %d, Tinh trang: %s\n",
                   books[i].id, books[i].title, books[i].author, books[i].genre, books[i].quantity, books[i].status);
            found = 1;
        }
    }
    if (!found) printf("Khong tim thay sach!\n");
}

// Hàm liệt kê sách quá hạn
void list_overdue() {
    char current_date[11];
    printf("Nhap ngay hien tai (dd/mm/yyyy): ");
    scanf("%s", current_date);

    int found = 0;
    for (int i = 0; i < borrow_count; i++) {
        if (borrows[i].returned == 0 && strcmp(borrows[i].due_date, current_date) < 0) {
            printf("Ma sinh vien: %s, Ma sach: %s, Ngay muon: %s, Ngay het han: %s\n",
                   borrows[i].student_id, borrows[i].book_id, borrows[i].borrow_date, borrows[i].due_date);
            found = 1;
        }
    }
    if (!found) printf("Khong co sach qua han!\n");
}

// Hàm lưu dữ liệu vào file
void save_to_file() {
    FILE *book_file = fopen("books.txt", "w");
    FILE *reader_file = fopen("readers.txt", "w");
    FILE *borrow_file = fopen("borrows.txt", "w");

    for (int i = 0; i < book_count; i++) {
        fprintf(book_file, "%s|%s|%s|%s|%d|%s\n", books[i].id, books[i].title, books[i].author, books[i].genre, books[i].quantity, books[i].status);
    }
    for (int i = 0; i < reader_count; i++) {
        fprintf(reader_file, "%s|%s\n", readers[i].name, readers[i].student_id);
    }
    for (int i = 0; i < borrow_count; i++) {
        fprintf(borrow_file, "%s|%s|%s|%s|%d\n", borrows[i].student_id, borrows[i].book_id, borrows[i].borrow_date, borrows[i].due_date, borrows[i].returned);
    }

    fclose(book_file);
    fclose(reader_file);
    fclose(borrow_file);
    printf("Luu du lieu thanh cong!\n");
}

// Hàm đọc dữ liệu từ file
void load_from_file() {
    FILE *book_file = fopen("books.txt", "r");
    FILE *reader_file = fopen("readers.txt", "r");
    FILE *borrow_file = fopen("borrows.txt", "r");

    if (book_file) {
        while (fscanf(book_file, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%s\n",
                      books[book_count].id, books[book_count].title, books[book_count].author,
                      books[book_count].genre, &books[book_count].quantity, books[book_count].status) != EOF) {
            book_count++;
        }
        fclose(book_file);
    }
    if (reader_file) {
        while (fscanf(reader_file, "%[^|]|%s\n", readers[reader_count].name, readers[reader_count].student_id) != EOF) {
            reader_count++;
        }
        fclose(reader_file);
    }
    if (borrow_file) {
        while (fscanf(borrow_file, "%[^|]|%[^|]|%[^|]|%[^|]|%d\n",
                      borrows[borrow_count].student_id, borrows[borrow_count].book_id,
                      borrows[borrow_count].borrow_date, borrows[borrow_count].due_date,
                      &borrows[borrow_count].returned) != EOF) {
            borrow_count++;
        }
        fclose(borrow_file);
    }
    printf("Doc du lieu thanh cong!\n");
}

// Hàm hiển thị menu
void display_menu() {
    printf("\n=== HE THONG QUAN LY THU VIEN ===\n");
    printf("1. Them sach\n");
    printf("2. Them ban doc\n");
    printf("3. Muon sach\n");
    printf("4. Tra sach\n");
    printf("5. Tim kiem sach\n");
    printf("6. Liet ke sach qua han\n");
    printf("7. Luu du lieu vao file\n");
    printf("8. Doc du lieu tu file\n");
    printf("0. Thoat\n");
    printf("Chon chuc nang: ");
}

int main() {
    int choice;
    load_from_file();
    do {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_book(); break;
            case 2: add_reader(); break;
            case 3: borrow_book(); break;
            case 4: return_book(); break;
            case 5: search_book(); break;
            case 6: list_overdue(); break;
            case 7: save_to_file(); break;
            case 8: load_from_file(); break;
            case 0: printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
    return 0;
}
