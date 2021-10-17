./server -service start


2y1u3xq67#
2y1u3xq67#
./server -config /config.toml -service install

./server -config config.toml -service install

grant all privileges on relay.* TO 'relayuser'@'%' identified by 'Adina856085';

CREATE USER 'relayuser'@'192.168.0.3';
CREATE USER relayuser@'%';
GRANT ALL PRIVILEGES ON pac.* to relayuser@'localhost' IDENTIFIED BY 'Adina856085';


server.exe -config config.toml