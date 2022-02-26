--Author: David Gibson
--CSCI 3700
--Homework 2

--Dropping tables to prevent conflicts
drop table history;
drop table currentLoan;
drop table book;
drop table member;

--Question 1: Creating tables
create table book
	(bookID			varchar(10) not null,
	 ISBN			varchar(13),
	 title			varchar(100),
	 author			varchar(40),
	 publish_year	varchar(4),
	 category		varchar(30),
	 primary key (bookID));
	 
create table member
	(memberID		varchar(10) not null,
	lastname		varchar(20),
	firstname		varchar(20),
	address			varchar(30),
	phone_number	varchar(30),
	limit			int,
	primary key (memberID));
	
create table currentLoan
	(memberID		varchar(10) not null,
	bookID			varchar(10) not null,
	loan_date		date,
	due_date		date,
	foreign key (memberID) references member(memberID),
	foreign key (bookID) references book(bookID));
	
create table history
	(memberID		varchar(10) not null,
	bookID			varchar(10) not null,
	loan_date		date not null,
	return_date		date,
	foreign key (memberID) references member(memberID),
	foreign key (bookID) references book(bookID));

--Question 2: Populating tables
insert into book values ('1', '1234567890123', 'Test Book', 'David Gibson', '1993', 'Non-Fiction');
insert into book values ('2', '4818299452040', 'Database Management Systems', 'Sam Samson', '2000', 'Non-Fiction');
insert into book values ('5', '9338468705145', 'Oracle', 'Twitch Streamer', '1993', 'Reference');
insert into book values ('6', '3436659179594', 'Database + Oracle', 'Generic Student', '2010', 'Non-Fiction');
insert into book values ('13', '4009821633360', 'Cooking With Quinoa', 'Mister Cook', '2017', 'Reference');
insert into book values ('1234', '3472620780065', 'Java and Other Languages', 'Qin Ding', '2019', 'Non-Fiction');
insert into book values ('56789', '7197190176258', 'Adventures of Dr Dandy', 'David Gibson', '2020', 'Children');
insert into book values ('60000', '7197190176258', 'Adventures of Dr Dandy', 'David Gibson', '2020', 'Children');
insert into book values ('10', '1457998462773', 'Thunderer', 'Felix Gilman', '2007', 'Fiction');
insert into book values ('234', '5081798844199', 'Mortal Coils', 'Eric Nylund', '2009', 'Fiction');
insert into book values ('654', '8534050581830', 'American Gods', 'Neil Gaiman', '2001', 'Fiction');
insert into book values ('789', '8534050581830', 'American Gods', 'Neil Gaiman', '2001', 'Fiction'); 

insert into member values ('1', 'Gibson', 'David', '1234 Street Street', '123-456-7890', 9);
insert into member values ('54', 'Sakuraba', 'Neku', '1234 Street Street', '123-456-7890', 6);
insert into member values ('23', 'Boseman', 'Chadwick', '1234 Street Street', '123-456-7890', 10);
insert into member values ('12', 'Wake', 'Alan', '1234 Street Street', '123-456-7890', 3);
insert into member values ('3', 'Faden', 'Jessie', '1234 Street Street', '123-456-7890', 1);

insert into currentLoan values('1', '2', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('23', '654', to_date('2020-08-24', 'yyyy-mm-dd'), to_date('2020-10-01', 'yyyy-mm-dd'));
insert into currentLoan values('3', '2', to_date('2020-06-01', 'yyyy-mm-dd'), to_date('2020-09-09', 'yyyy-mm-dd'));
insert into currentLoan values('1', '234', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('1', '789', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('1', '5', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('1', '6', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('1', '10', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('23', '234', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('23', '789', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('23', '5', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('23', '6', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));
insert into currentLoan values('23', '10', to_date('2020-08-09', 'yyyy-mm-dd'), to_date('2020-12-09', 'yyyy-mm-dd'));

insert into history values('1', '654', to_date('2018-04-04', 'yyyy-mm-dd'), to_date('2018-04-28', 'yyyy-mm-dd'));
insert into history values('23', '10', to_date('2016-10-02', 'yyyy-mm-dd'), to_date('2016-10-10', 'yyyy-mm-dd'));
insert into history values('54', '1234', to_date('2015-12-04', 'yyyy-mm-dd'), to_date('2016-01-28', 'yyyy-mm-dd'));

commit;

--QUERIES
--Question 3: Find the book ID, title, author, and publish-year of all the books with the words “Database” and “Oracle” in the title
select bookID, title, author, publish_year
from book
where title like '%Database%' or
		title like '%Oracle%'
order by publish_year desc;

--Question 4: Find the memberID, firstname, and last name of the member(s) who are currently borrowing the book “Database Management Systems”.
select member.memberID, firstname, lastname
from member, currentLoan
where member.memberID = currentLoan.memberID and
		currentLoan.bookID = '2';
	
--Question 5: Find the bookID and title of the books which have never been checked out in the past or currently.
select book.bookID, title
from book
minus
select book.bookID, title
from book, currentLoan, history
where book.bookID = currentLoan.bookID or
		book.bookID = history. bookID;

--Question 6: For each different book (ISBN and title), list the number of copies.
select ISBN, count(bookID)
from book
group by ISBN;

--Question 7: List the memberID, lastname, and firstname of members who are currently borrowing more than 5 books.
select member.memberID, lastname, firstname
from member, currentLoan
where member.memberID = currentLoan.memberID
having count(currentLoan.memberID) > 5
group by member.memberID, lastname, firstname;