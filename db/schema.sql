DROP TABLE IF EXISTS access_levels CASCADE;
DROP FUNCTION IF EXISTS unixtime(t timestamp) CASCADE;
DROP FUNCTION IF EXISTS unixnow() CASCADE;
DROP FUNCTION IF EXISTS liketags(m text) CASCADE;
DROP TABLE IF EXISTS users_history CASCADE;
DROP TABLE IF EXISTS posts_history CASCADE;
DROP TABLE IF EXISTS sessions CASCADE;
DROP TABLE IF EXISTS votes CASCADE;
DROP TABLE IF EXISTS posts CASCADE;
DROP TABLE IF EXISTS tags CASCADE;
DROP TABLE IF EXISTS users CASCADE;
DROP TYPE IF EXISTS action CASCADE;


CREATE TYPE action AS ENUM ('INSERT', 'UPDATE', 'DELETE');

CREATE TABLE tags (
  name TEXT UNIQUE PRIMARY KEY, 
  type INTEGER, 
  introduced BIGINT, 
  changed BIGINT
);

CREATE TABLE users (
  id SERIAL UNIQUE PRIMARY KEY,
  access INTEGER,
  name TEXT,
  password_hash TEXT,
  email TEXT,
  joined BIGINT,
  score INTEGER,
  changer INTEGER REFERENCES users(id),
  changed BIGINT
);

CREATE TABLE sessions (
  hash TEXT UNIQUE PRIMARY KEY,
  userid INTEGER REFERENCES users(id),
  created BIGINT
);


CREATE TABLE posts (
  id SERIAL UNIQUE PRIMARY KEY, 
  name TEXT,
  path TEXT,
  hash TEXT,
  size INTEGER,
  score INTEGER,
  userid INTEGER REFERENCES users(id),
  posted BIGINT,
  tags TEXT[],
  changer INTEGER REFERENCES users(id),
  changed BIGINT
);

CREATE TABLE votes (
  id SERIAL UNIQUE PRIMARY KEY,
  postid INTEGER REFERENCES posts(id),
  amount INTEGER,
  userid INTEGER REFERENCES users(id)
);

CREATE TABLE posts_history (
  id SERIAL UNIQUE PRIMARY KEY,
  changer INTEGER REFERENCES users(id),
  changed BIGINT,
  action ACTION,
  postid INTEGER REFERENCES posts(id),
  userid INTEGER REFERENCES users(id),
  old_name TEXT,
  new_name TEXT,
  old_score INTEGER,
  new_score INTEGER,
  old_tags TEXT[],
  new_tags TEXT[]
);

CREATE TABLE users_history (
  id SERIAL UNIQUE PRIMARY KEY,
  changer INTEGER REFERENCES users(id),
  changed BIGINT,
  action ACTION,
  userid INTEGER REFERENCES users(id),
  old_access INTEGER,
  new_access INTEGER,
  old_score INTEGER,
  new_score INTEGER,
  old_password_hash TEXT,
  new_password_hash TEXT,
  old_email TEXT,
  new_email TEXT,
  old_name TEXT,
  new_name TEXT
);

CREATE RULE log_users_insert AS ON INSERT TO users
  DO ALSO INSERT INTO users_history VALUES (
    DEFAULT,
    NULL,
    NEW.changed,
    'INSERT',
    NULL,
    NULL,
    NEW.access,
    NULL,
    NEW.score,
    NULL,
    NEW.password_hash,
    NULL,
    NEW.email,
    NULL,
    NEW.name
  );
  
CREATE RULE log_users_update AS ON UPDATE TO users
  DO ALSO INSERT INTO users_history VALUES (
    DEFAULT,
    NEW.changer,
    NEW.changed,
    'UPDATE',
    NEW.id,
    OLD.access,
    NEW.access,
    OLD.score,
    NEW.score,
    OLD.password_hash,
    NEW.password_hash,
    OLD.email,
    NEW.email,
    OLD.name,
    NEW.name
  );

CREATE RULE log_users_delete AS ON DELETE TO users
  DO ALSO INSERT INTO users_history VALUES (
    DEFAULT,
    DEFAULT,
    floor(extract(EPOCH from now())),
    'DELETE',
    NULL,
    OLD.access,
    NULL,
    OLD.score,
    NULL,
    OLD.password_hash,
    NULL,
    OLD.email,
    NULL,
    OLD.name,
    NULL
  );
  
CREATE RULE log_posts_insert AS ON INSERT TO posts
  DO ALSO INSERT INTO posts_history VALUES (
    DEFAULT,
    NEW.changer,
    NEW.changed,
    'INSERT',
	NEW.id-1,
	NEW.userid,
	NULL,
	NEW.name,
	NULL,
	NEW.score,
	NULL,
	NEW.tags
  );
  
CREATE RULE log_posts_update AS ON UPDATE TO posts
  DO ALSO INSERT INTO posts_history VALUES (
    DEFAULT,
    NEW.changer,
    NEW.changed,
    'UPDATE',
	NEW.id,
	NEW.userid,
	OLD.name,
	NEW.name,
	OLD.score,
	NEW.score,
	OLD.tags,
	NEW.tags
  );
  
CREATE RULE log_posts_delete AS ON DELETE TO posts
  DO ALSO INSERT INTO posts_history VALUES (
    DEFAULT,
    DEFAULT,
	floor(extract(EPOCH from now())),
    'DELETE',
	OLD.id,
	OLD.userid,
	OLD.name,
	NULL,
	OLD.score,
	NULL,
	OLD.tags,
	NULL
  );

CREATE FUNCTION liketags(m text) RETURNS text[] AS $$ DECLARE set text[]; BEGIN select array_agg(name) into set from tags where name like m; return set; END; $$ LANGUAGE plpgsql;
CREATE FUNCTION unixtime(t timestamp) RETURNS bigint AS $$ BEGIN return floor(extract(EPOCH from t)); END; $$ LANGUAGE plpgsql;
CREATE FUNCTION unixnow() RETURNS bigint AS $$ BEGIN return floor(extract(EPOCH from now())); END; $$ LANGUAGE plpgsql;



CREATE TABLE access_levels (
	value INTEGER,
	name TEXT
);

INSERT INTO access_levels VALUES (1000,'Member');
INSERT INTO access_levels VALUES (100,'Moderator');
INSERT INTO access_levels VALUES (10,'Adminisrator');
INSERT INTO access_levels VALUES (1,'Root Admin');
INSERT INTO access_levels VALUES (0,'Deus');
INSERT INTO access_levels VALUES (-1,'Anonymous');
INSERT INTO access_levels VALUES (-10,'Unholy Nomad');
INSERT INTO access_levels VALUES (-100,'Restricted');
INSERT INTO access_levels VALUES (-1000,'Banned');

INSERT INTO users VALUES (DEFAULT,0,'Deus','I am Not to be logged in, mortal','deus@machina',unixnow(),-1,NULL,unixnow());
