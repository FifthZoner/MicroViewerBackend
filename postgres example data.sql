truncate table boards;
truncate table chips;
truncate table categories;
truncate table manufacturers;

insert into categories values (1, 'Evaluation boards');
insert into categories values (2, 'Single board computers');
insert into categories values (3, 'Control boards');

insert into manufacturers values (101, 'Bigtree-Tech', 'https://bigtree-tech.com/');
insert into manufacturers values (102, '3D Mellow', 'https://3dmellow.com/');

insert into manufacturers values (104, 'LDO Motors', 'https://ldomotors.com/');
insert into manufacturers values (105, 'Raspberry Pi', 'https://bigtree-tech.com/');
insert into manufacturers values (106, 'Orange Pi', 'http://www.orangepi.org/');
insert into manufacturers values (107, 'ST Microelectronics', 'https://www.st.com/content/st_com/en.html');

insert into chips values (201, 'STM32F072', 'https://www.empowerlaptop.com/p/stm32f072rvt6/', 'https://www.st.com/en/microcontrollers-microprocessors/stm32f072rb.html#documentation');
insert into chips values (202, 'STM32G0B1', 'https://www.mouser.tw/new/stmicroelectronics/stm-stm32g0b1-stm32g0c1-mcus/', 'https://www.st.com/en/microcontrollers-microprocessors/stm32g0-series/documentation.html');
insert into chips values (203, 'Broadcom BCM2837', 'https://willy-tech.de/wp-content/uploads/2016/03/Raspberry-Pi-3-vorgestellt-1.jpg', 'https://www.alldatasheet.com/datasheet-pdf/pdf/1572343/BOARDCOM/BCM2837.html');
insert into chips values (204, 'Broadcom BCM2712', '', '');
insert into chips values (205, 'Broadcom BCM2711', '', '');
insert into chips values (206, 'STM32F446', '', '');
insert into chips values (207, 'STM32F103RB', '', '');
insert into chips values (208, 'AllWinner H6', '', '');

insert into boards values(301, 'EBB 36 CAN V1.0', 'https://www.diyelectronics.co.za/store/21674-thickbox_default/bigtreetech-ebb36-can-v12-for-klipper-expansion.jpg', 101, 3, 201, 'https://github.com/bigtreetech/EBB/tree/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0/Hardware/EBB36%20CAN%20V1.0-SCH.pdf', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0/Hardware/EBB36%20CAN%20V1.0-PIN.png', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0/Hardware/EBB36%20CAN%20V1.0-SIZE.pdf');
insert into boards values(302, 'EBB 36 CAN V1.1', 'https://www.diyelectronics.co.za/store/21674-thickbox_default/bigtreetech-ebb36-can-v12-for-klipper-expansion.jpg', 101, 3, 202, 'https://github.com/bigtreetech/EBB/tree/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB36%20CAN%20V1.1%20and%20V1.2', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB36%20CAN%20V1.1%20and%20V1.2/Hardware/BIGTREETECH%20EBB36%20CAN%20V1.1-SCH.pdf', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB36%20CAN%20V1.1%20and%20V1.2/Hardware/EBB36%20CAN%20V1.1%26V1.2-PIN.png', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB36%20CAN%20V1.1%20and%20V1.2/Hardware/BIGTREETECH%20EBB36%20CAN%20V1.1-SIZE.pdf');
insert into boards values(303, 'EBB 42 CAN V1.0', 'https://www.diyelectronics.co.za/store/21671-thickbox_default/bigtreetech-ebb42-can-v12-for-klipper-expansion.jpg', 101, 3, 201, 'https://github.com/bigtreetech/EBB/tree/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB42%20CAN%20V1.0/Hardware/EBB42%20CAN%20V1.0-SCH.pdf', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB42%20CAN%20V1.0/Hardware/EBB42%20CAN%20V1.0-PIN.png', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB42%20CAN%20V1.0/Hardware/EBB42%20CAN%20V1.0-SIZE.pdf');
insert into boards values(304, 'EBB 42 CAN V1.1', 'https://www.diyelectronics.co.za/store/21671-thickbox_default/bigtreetech-ebb42-can-v12-for-klipper-expansion.jpg', 101, 3, 202, 'https://github.com/bigtreetech/EBB/tree/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB42%20CAN%20V1.1%20and%20V1.2', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB42%20CAN%20V1.1%20and%20V1.2/Hardware/BIGTREETECH%20EBB42%20CAN%20V1.1-SCH.pdf', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB42%20CAN%20V1.1%20and%20V1.2/Hardware/EBB42%20CAN%20V1.1%26V1.2-PIN.png', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.1%20and%20V1.2%20(STM32G0B1)/EBB42%20CAN%20V1.1%20and%20V1.2/Hardware/BIGTREETECH%20EBB42%20CAN%20V1.1-SIZE.pdf');
insert into boards values(305, 'Raspberry Pi 3B', 'https://assets.raspberrypi.com/static/532b4c25752c4235d76cc41051baf9ab/9ff6b/877fb653-7b43-4931-9cee-977a22571f65_3b%2BAngle%2B2%2Brefresh.webp', 105, 2, 203, '', '', '', '');
insert into boards values(306, 'Raspberry Pi 4B', 'https://upload.wikimedia.org/wikipedia/commons/thumb/1/10/Raspberry_Pi_4_Model_B_-_Top.jpg/1920px-Raspberry_Pi_4_Model_B_-_Top.jpg', 105, 2, 205, '', '', '', '');
insert into boards values(307, 'Raspberry Pi 5', 'https://assets.raspberrypi.com/static/8f6eca535dbb23a21eb41a748050e3a0/f7ad0/16gb.webp', 105, 2, 204, '', '', '', '');
insert into boards values(308, 'Voron Leviathan', 'https://raw.githubusercontent.com/MotorDynamicsLab/Leviathan/master/Media/product_img_web2.avif', 104, 3, 206, '', '', '', '');
insert into boards values(309, 'STM32 Nucleo-64 F103RB', 'https://www.st.com/bin/ecommerce/api/image.PF259875.en.feature-description-include-personalized-no-cpn-medium.jpg', 107, 1, 207, '', '', '', '');
insert into boards values(310, 'Orange Pi 3', 'https://orangepi.com/image/cache/catalog/orangepi/op3jpg-500x500.jpg', 106, 2, 208, '', '', '', '');

select setval('ids', 401, true);

select * from categories;