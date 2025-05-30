truncate table boards;
truncate table chips;
truncate table categories;
truncate table manufacturers;

insert into categories values (1, 'Evaluation boards');
insert into categories values (2, 'Single board computers');
insert into categories values (3, 'Control boards');

insert into manufacturers values (101, 'Bigtree-Tech', 'https://bigtree-tech.com/');
insert into manufacturers values (102, '3D Mellow', 'https://3dmellow.com/');
insert into manufacturers values (103, 'Fysetc', 'https://www.fysetc.com/');
insert into manufacturers values (104, 'Raspberry Pi', 'https://bigtree-tech.com/');
insert into manufacturers values (105, 'Orange Pi', 'http://www.orangepi.org/');

insert into chips values (201, 'STM32F072', 'https://www.empowerlaptop.com/p/stm32f072rvt6/', 'https://www.st.com/en/microcontrollers-microprocessors/stm32f072rb.html#documentation');
insert into chips values (202, 'STM32G0B1', 'https://www.mouser.tw/new/stmicroelectronics/stm-stm32g0b1-stm32g0c1-mcus/', 'https://www.st.com/en/microcontrollers-microprocessors/stm32g0-series/documentation.html');

insert into boards values(301, 'EBB 36 CAN V1.0', 'https://www.diyelectronics.co.za/store/21674-thickbox_default/bigtreetech-ebb36-can-v12-for-klipper-expansion.jpg', 101, 3, 201, 'https://github.com/bigtreetech/EBB/tree/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0/Hardware/EBB36%20CAN%20V1.0-SCH.pdf', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0/Hardware/EBB36%20CAN%20V1.0-PIN.png', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0/Hardware/EBB36%20CAN%20V1.0-SIZE.pdf');
insert into boards values(302, 'EBB 42 CAN V1.0', 'https://www.diyelectronics.co.za/store/21671-thickbox_default/bigtreetech-ebb42-can-v12-for-klipper-expansion.jpg', 101, 3, 201, 'https://github.com/bigtreetech/EBB/tree/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB36%20CAN%20V1.0', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB42%20CAN%20V1.0/Hardware/EBB42%20CAN%20V1.0-SCH.pdf', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB42%20CAN%20V1.0/Hardware/EBB42%20CAN%20V1.0-PIN.png', 'https://github.com/bigtreetech/EBB/blob/master/EBB%20CAN%20V1.0%20(STM32F072)/EBB42%20CAN%20V1.0/Hardware/EBB42%20CAN%20V1.0-SIZE.pdf');

select setval('ids', 401, true);

select * from categories;