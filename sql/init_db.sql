-- Таблица вертолетов
CREATE TABLE helicopters (
    id INTEGER PRIMARY KEY,
    number TEXT UNIQUE NOT NULL,
    model TEXT NOT NULL,
    manufacture_date DATE NOT NULL,
    max_payload REAL NOT NULL,
    last_repair DATE NOT NULL,
    flight_hours_remaining INTEGER NOT NULL
);

-- Таблица экипажей
CREATE TABLE crew_members (
    id INTEGER PRIMARY KEY,
    tab_number TEXT UNIQUE NOT NULL,
    name TEXT NOT NULL,
    position TEXT NOT NULL,
    experience INTEGER NOT NULL,
    address TEXT NOT NULL,
    birth_year INTEGER NOT NULL,
    helicopter_id INTEGER,
    FOREIGN KEY(helicopter_id) REFERENCES helicopters(id)
);

-- Таблица рейсов
CREATE TABLE flights (
    id INTEGER PRIMARY KEY,
    date DATE NOT NULL,
    helicopter_id INTEGER,
    flight_code TEXT NOT NULL,
    cargo_weight REAL NOT NULL,
    passengers INTEGER NOT NULL,
    duration_hours REAL NOT NULL,
    cost REAL NOT NULL,
    is_special BOOLEAN NOT NULL DEFAULT 0,
    FOREIGN KEY(helicopter_id) REFERENCES helicopters(id)
);

-- Таблица пользователей
CREATE TABLE users (
    id INTEGER PRIMARY KEY,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    role TEXT NOT NULL CHECK(role IN ('commander', 'crew'))
);

-- Таблица для начисления денег
CREATE TABLE earnings (
    id INTEGER PRIMARY KEY,
    crew_member_id INTEGER,
    amount REAL NOT NULL,
    period_start DATE NOT NULL,
    period_end DATE NOT NULL,
    FOREIGN KEY(crew_member_id) REFERENCES crew_members(id)
);

-- Триггер для проверки ресурса вертолета
CREATE TRIGGER check_flight_hours
BEFORE INSERT ON flights
FOR EACH ROW
BEGIN
    SELECT RAISE(ABORT, 'Превышен ресурс летного времени для вертолета')
    FROM helicopters
    WHERE id = NEW.helicopter_id
    AND (flight_hours_remaining - NEW.duration_hours) < 0;
END;

-- Индексы для оптимизации
CREATE INDEX idx_flight_helicopter ON flights(helicopter_id);
CREATE INDEX idx_crew_helicopter ON crew_members(helicopter_id);