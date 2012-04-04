drop view if exists users_rights_view;
drop view if exists users_groups_rights_view;
drop view if exists users_groups_view ;
drop view if exists groups_rights_view ;
drop view if exists users_static_view;

drop table if exists groups_rights;
drop table if exists rights;
drop table if exists users_groups;
drop table if exists groups;
drop table if exists users_static;
drop table if exists users;





create table users (
    id serial PRIMARY KEY,
    name text UNIQUE NOT NULL,
    password_hash text,
    email text
);

create table users_static (
    id serial PRIMARY KEY,
    ip text UNIQUE NOT NULL,
    user_id integer REFERENCES users(id)
);

create view users_static_view as
    select
        name, ip
    from users_static
        inner join users on user_id = users.id;

create table groups (
    id serial PRIMARY KEY,
    name text UNIQUE
);

create table users_groups (
    user_id integer REFERENCES users(id),
    group_id integer REFERENCES groups(id),
    PRIMARY KEY(user_id,group_id)
);

create view users_groups_view as
    select
        users.name,
        users.password_hash,
        users.email,
        groups.name as group
    from users_groups
        inner join users on users_groups.user_id = users.id
        inner join groups on users_groups.group_id = groups.id;

create table rights (
    id serial PRIMARY KEY,
    name text UNIQUE
);

create table groups_rights (
    group_id integer REFERENCES groups(id),
    right_id integer REFERENCES rights(id),
    PRIMARY KEY(group_id,right_id)
);

create view groups_rights_view as
    select
        groups.name as group,
        rights.name as right
    from groups_rights
        inner join groups on groups_rights.group_id = groups.id
        inner join rights on groups_rights.right_id = rights.id;


create view users_groups_rights_view as
    select
        users.name,
        users.password_hash,
        users.email,
        groups.name as group,
        rights.name as right
    from users_groups
        inner join users on users_groups.user_id = users.id
        inner join groups on users_groups.group_id = groups.id
        inner join groups_rights on groups_rights.group_id = users_groups.group_id
        inner join rights on groups_rights.right_id = rights.id;


create view users_rights_view as select distinct name,"right" from users_groups_rights_view ;




delete from rights;
insert into rights(name) values('view');
insert into rights(name) values('signup');
insert into rights(name) values('signin');
insert into rights(name) values('upload');
insert into rights(name) values('delete');
insert into rights(name) values('rateview');
insert into rights(name) values('rateup');
insert into rights(name) values('ratedown');
insert into rights(name) values('pause');
insert into rights(name) values('stop');
insert into rights(name) values('play');
insert into rights(name) values('clean');
insert into rights(name) values('commentview');
insert into rights(name) values('commentadd');
insert into rights(name) values('commentdel');

delete from groups;
insert into groups(name) values('banned');
insert into groups(name) values('anonymous');
insert into groups(name) values('user');
insert into groups(name) values('moderator');
insert into groups(name) values('admin');

delete from users;
insert into users(name) values('deus');
insert into users(name) values('admin');
insert into users(name,password_hash) values('anonymous','');

delete from users_static;
insert into users_static(ip,user_id)
select v_ip,users.id from users,
    (values
        ('666.666.666.666','deus')
    ) v(v_ip,v_user)
where users.name=v.v_user;


delete from groups_rights;
insert into groups_rights
select groups.id, rights.id from groups, rights,
    (values
        ('anonymous','view'),
        ('anonymous','signup'),
        ('anonymous','signin'),
        ('anonymous','rateview'),
        ('anonymous','commentview'),

        ('user','view'),
        ('user','signup'),
        ('user','signin'),
        ('user','rateview'),
        ('user','rateup'),
        ('user','ratedown'),
        ('user','commentview'),
        ('user','commentadd'),
        ('user','upload'),

        ('moderator','view'),
        ('moderator','signup'),
        ('moderator','signin'),
        ('moderator','rateview'),
        ('moderator','rateup'),
        ('moderator','ratedown'),
        ('moderator','commentview'),
        ('moderator','commentadd'),
        ('moderator','commentdel'),
        ('moderator','upload'),
        ('moderator','delete'),
        ('moderator','clean'),

        ('admin','view'),
        ('admin','signup'),
        ('admin','signin'),
        ('admin','rateview'),
        ('admin','rateup'),
        ('admin','ratedown'),
        ('admin','commentview'),
        ('admin','commentadd'),
        ('admin','commentdel'),
        ('admin','upload'),
        ('admin','delete'),
        ('admin','clean'),
        ('admin','play'),
        ('admin','stop'),
        ('admin','pause')
    ) v(v_group,v_right)
where groups.name=v.v_group and rights.name=v.v_right;

delete from users_groups;
insert into users_groups
select users.id, groups.id from users, groups,
    (values
        ('deus','admin'),
        ('anonymous','anonymous')
    ) v(v_user,v_group)
where users.name=v.v_user and groups.name=v.v_group;
