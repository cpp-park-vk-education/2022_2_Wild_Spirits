drop schema public CASCADE;
create schema public;

create table if not exists Users (
	id int primary key generated always as identity,
	nickname varchar unique not null,
	password_hash char(256) not null
);

create table if not exists Campaigns (
	id int primary key generated always as identity,
	name varchar not null,
	description text
);

--create table if not exists Configs (
--	id int primary key generated always as identity,
--	autoapply bool
--);

create table if not exists Rooms (
	id int primary key generated always as identity,
	DM_id int references Users(id) not null,
	campaign_id int references Campaigns(id) not null,
--	config_id int references Configs(id)
);

create table if not exists UserRoomMap (
	id int primary key generated always as identity,
	user_id int references Users(id) not null,
	room_id int references Rooms(id) not null
);

create table if not exists Images (
	id int primary key generated always as identity,
	path varchar not null
);

create table if not exists Locations (
	id int primary key generated always as identity,
	campaign_id int references Campaigns(id) not null,
	name varchar not null,
	background_image_id int references Images(id),
	size_x int not null,
	size_y int not null
);

create table if not exists "Characters" (
	id int primary key generated always as identity,
	name varchar not null,
	max_hp int not null,
	image_id int references Images(id) not null,
	meta_information json
);

create table if not exists CharacterInstances (
	id int primary key generated always as identity,
	character_id int references "Characters"(id) not null,
	hp int not null,
	location_id int references Locations(id) not null,
	pos_x int not null,
	pos_y int not null
);

create table if not exists Players (
	id int primary key generated always as identity,
	character_instance_id int references CharacterInstances(id),
	campaign_id int references Campaigns(id) not null,
	race varchar not null,
	"class" varchar not null
);

create table if not exists Items (
	id int primary key generated always as identity,
	name varchar not null,
	"type" varchar not null,
	effect json
);

create table if not exists ItemStates (
	id int primary key generated always as identity,
	state json not null
);

create table if not exists Inventories (
	id int primary key generated always as identity,
	character_instance_id int references CharacterInstances(id) not null,
	item_id int references Items(id) not null
);
