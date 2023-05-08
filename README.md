# EUCLIDEAN
## Giới thiệu
Game code bởi Trần Vũ Đức Huy - 22021111
## Hướng dẫn chơi game
### 1. Start menu
- Cột trái là mục `Glossary` gồm những kiến thức cần có.

- Cột phải là mục `Techniques` gồm những hướng đi có thể dùng để xử lý.

- Cột giữa là mục `Contents` gồm những game với đề bài ứng với mỗi content, trong đó có sẵn 2 bài để màu cam nhạt đã có để thử sức còn những bài còn lại cần dùng gói Premium :v.

  ![Menu](https://user-images.githubusercontent.com/125182856/236879638-a3136371-6151-4d2c-9b14-41a02b1a7390.png)

### 2. In game
#### Các đối tượng
- Sau khi nhấp chuột thì đối tượng tương ứng sẽ đổi màu
- Ở giữa là bảng kích thước 7x7 để chơi trong đó có sẵn 49 điểm nguyên và 14 đường lưới để sử dụng.
- Cột trái `Tools` gồm các công cụ:

  `New point`: Dùng để tạo 1 điểm thỏa mãn 3 điều kiện sau:
    
      Là giao điểm của 2 đường thẳng đã có cắt nhau.
    
      Nằm trong bảng.
    
      Chưa xuất hiện trước đó.
  
  `New line`: Dùng để tạo 1 đường thẳng thỏa mãn 2 điều kiện sau:
  
      Đi qua 2 điểm đã có
    
      Chưa xuất hiện trước đó
      
    ![NewLine](https://user-images.githubusercontent.com/125182856/236879687-950da29e-d6b0-4a5b-86c7-927b58c6e955.png)
    
  `Create`: Dùng để tạo điểm hoặc đường thẳng sau khi đã chọn được 2 đối tượng cần thiết.
  
    ![NewLineCreated](https://user-images.githubusercontent.com/125182856/236886916-f106229e-3071-4c29-9689-6b5ddd2c59f4.png)
   
  `Delete`: Dùng để xóa các điểm hoặc đường thẳng đang chọn và quay về trước khi chọn `New point` hay `New line`.
   
   `Done!!!`: Dùng để nộp bài.
   
- Cột `Points` gồm các điểm mới không thuộc 49 điểm nguyên trên bảng.
- Cột `Lines` gồm các đường thẳng mới không thuộc 14 đường lưới trên bảng.
#### Luật chơi
- Với các ô ta chỉ có thể chọn để khi đang sáng màu.

    Ảnh minh họa các vị trí màu cam nhạt chọn đối tượng bằng nhấp chuột.
    
  ![Avalible ](https://user-images.githubusercontent.com/125182856/236878919-1418ce96-665f-4411-b57d-89cb5eb3b9c5.png)
  
- Sau khi nhấp chuột thì đối tượng tương ứng sẽ đổi màu

  ![ChoosingLine](https://user-images.githubusercontent.com/125182856/236879665-1fc33269-cfab-423c-aac1-1be3e486ce74.png)

- Sau khi ấn `New line`, ta chỉ có thể chọn các điểm sau:
    
    49 điểm nguyên chọn bằng cách nhấp trên bảng và thấy đổi màu.
    
    Các điểm đã tạo chọn bằng cách nhấp vào ô tương ứng bên cột `Points`.
    
- Sau khi ấn `New point`, ta chỉ có thể chọn các đường thẳng sau:

    7 đường lưới dọc chọn bằng cách nhấp vào gần đầu đoạn ở bên trên.
    
    7 đường lưới ngang chọn bằng cách nhấp vào gần đầu đoạn bên trái.
    
    Các đường thẳng đã tạo chọn bằng cách nhấp vào ô tương ứng bên cột `Lines`.
### 3. End game
- Nhấp vô `BACK TO MENU` để quay về start menu chơi tiếp.
![End](https://user-images.githubusercontent.com/125182856/236879676-2f71ee49-2e8a-4b9d-a207-36cf184571d0.png)

### 4. Hướng phát triển
- Tools mới:
 
  `New circle`: Cho phép tạo đường tròn.
