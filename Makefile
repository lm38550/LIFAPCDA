SDL: bin/mainSDL.exe

windows: bin/mainWIN.exe

txt: bin/mainTXT.exe

bin/mainSDL.exe: obj/arrow.o obj/bomb.o obj/bombBag.o obj/bow.o obj/chest.o obj/collectible.o obj/displaySDL.o obj/door.o obj/enemy.o obj/entity.o obj/fire.o obj/inventory.o obj/item.o obj/mainSDL.o obj/map.o obj/lantern.o obj/player.o obj/sword.o obj/tile.o obj/vec2f.o
	g++ -o bin/mainSDL.exe obj/arrow.o obj/bomb.o obj/bombBag.o obj/bow.o obj/chest.o obj/collectible.o obj/displaySDL.o obj/door.o obj/enemy.o obj/entity.o obj/fire.o obj/inventory.o obj/item.o obj/mainSDL.o obj/map.o obj/lantern.o obj/player.o obj/sword.o obj/tile.o obj/vec2f.o -lSDL2 -lSDL2_image -Wall -lSDL2_ttf

bin/mainWIN.exe: obj/arrow.o obj/bomb.o obj/bombBag.o obj/bow.o obj/chest.o obj/collectible.o obj/displayWIN.o obj/door.o obj/enemy.o obj/entity.o obj/fire.o obj/inventory.o obj/item.o obj/mainSDL.o obj/map.o obj/lantern.o obj/player.o obj/sword.o obj/tile.o obj/vec2f.o
	g++ -o bin/mainWIN.exe obj/arrow.o obj/bomb.o obj/bombBag.o obj/bow.o obj/chest.o obj/collectible.o obj/displayWIN.o obj/door.o obj/enemy.o obj/entity.o obj/fire.o obj/inventory.o obj/item.o obj/mainSDL.o obj/map.o obj/lantern.o obj/player.o obj/sword.o obj/tile.o obj/vec2f.o -L bin -lmingw32 -lSDL2 -lSDL2_image -Wall -lSDL2_ttf

bin/mainTXT.exe: obj/arrow.o obj/bomb.o obj/bombBag.o obj/bow.o obj/chest.o obj/collectible.o obj/displayTXT.o obj/door.o obj/enemy.o obj/entity.o obj/fire.o obj/inventory.o obj/item.o obj/mainTXT.o obj/map.o obj/lantern.o obj/player.o obj/tile.o obj/vec2f.o obj/winTxt.o
	g++ -o bin/mainTXT.exe obj/arrow.o obj/bomb.o obj/bombBag.o obj/bow.o obj/chest.o obj/collectible.o obj/displayTXT.o obj/door.o obj/enemy.o obj/entity.o obj/fire.o obj/inventory.o obj/item.o obj/mainTXT.o obj/map.o obj/lantern.o obj/player.o obj/tile.o obj/vec2f.o obj/winTxt.o -Wall

obj/arrow.o: src/arrow.cpp include/Arrow.h include/Vec2f.h include/Utils.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h
	g++ -c src/arrow.cpp -o obj/arrow.o -I include -I library -Wall

obj/bomb.o: src/bomb.cpp include/Bomb.h include/Vec2f.h include/Utils.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h
	g++ -c src/bomb.cpp -o obj/bomb.o -I include -I library -Wall

obj/bombBag.o: src/bombBag.cpp include/BombBag.h include/Vec2f.h include/Utils.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h
	g++ -c src/bombBag.cpp -o obj/bombBag.o -I include -I library -Wall

obj/bow.o: src/bow.cpp include/Bow.h include/Vec2f.h include/Utils.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h
	g++ -c src/bow.cpp -o obj/bow.o -I include -I library -Wall

obj/chest.o: src/chest.cpp include/Chest.h include/Vec2f.h
	g++ -c src/chest.cpp -o obj/chest.o -I include -I library -Wall

obj/collectible.o: src/collectible.cpp include/Collectible.h include/Vec2f.h
	g++ -c src/collectible.cpp -o obj/collectible.o -I include -I library -Wall

obj/displayTXT.o: src/displayTXT.cpp include/DisplayTXT.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h include/Enemy.h include/Vec2f.h include/Utils.h library/winTxt.h
	g++ -c src/displayTXT.cpp -o obj/displayTXT.o -I include -I library -Wall

obj/displaySDL.o: src/displaySDL.cpp include/DisplaySDL.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h include/Enemy.h include/Vec2f.h include/Utils.h include/Inventory.h include/Item.h
	g++ -c src/displaySDL.cpp -o obj/displaySDL.o -I/usr/include/SDL2 -I include -D_REENTRANT -I library -Wall

obj/displayWIN.o: src/displaySDL.cpp include/DisplaySDL.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h include/Enemy.h include/Vec2f.h include/Utils.h include/Inventory.h include/Item.h
	g++ -c src/displaySDL.cpp -o obj/displayWIN.o -I C:/SDL2-w64/include -I include -D_REENTRANT -I library -Wall

obj/door.o: src/door.cpp include/Door.h include/Vec2f.h
	g++ -c src/door.cpp -o obj/door.o -I include -I library -Wall

obj/enemy.o: src/enemy.cpp include/Enemy.h include/Vec2f.h include/Utils.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h
	g++ -c src/enemy.cpp -o obj/enemy.o -I include -I library -Wall

obj/entity.o: src/entity.cpp include/Entity.h include/Vec2f.h
	g++ -c src/entity.cpp -o obj/entity.o -I include -I library -Wall

obj/fire.o: src/fire.cpp include/Fire.h include/Vec2f.h include/Utils.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h
	g++ -c src/fire.cpp -o obj/fire.o -I include -I library -Wall

obj/inventory.o: src/inventory.cpp include/Inventory.h include/Item.h
	g++ -c src/inventory.cpp -o obj/inventory.o -I include -I library -Wall

obj/item.o: src/item.cpp include/Item.h
	g++ -c src/item.cpp -o obj/item.o -I include -I library -Wall

obj/mainTXT.o: src/mainTXT.cpp include/DisplayTXT.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h include/Enemy.h include/Vec2f.h include/Utils.h
	g++ -c src/mainTXT.cpp -o obj/mainTXT.o -I include -I library -Wall

obj/mainSDL.o: src/mainSDL.cpp include/DisplaySDL.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h include/Enemy.h include/Vec2f.h include/Utils.h
	g++ -c src/mainSDL.cpp -o obj/mainSDL.o -I include -I/usr/include/SDL2 -D_REENTRANT -I library -Wall

obj/map.o: src/map.cpp include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Inventory.h include/Door.h include/Enemy.h include/Vec2f.h include/Utils.h
	g++ -c src/map.cpp -o obj/map.o -I include -I library -Wall

obj/lantern.o: src/lantern.cpp include/Lantern.h include/Vec2f.h include/Utils.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h
	g++ -c src/lantern.cpp -o obj/lantern.o -I include -I library -Wall

obj/sword.o: src/sword.cpp include/Map.h
	g++ -c src/sword.cpp -o obj/sword.o -I include -Wall

obj/player.o: src/player.cpp include/Player.h include/Vec2f.h include/Utils.h include/Map.h include/Tile.h include/Chest.h include/Entity.h include/Door.h include/Sword.h include/Inventory.h
	g++ -c src/player.cpp -o obj/player.o -I include -I library -Wall

obj/tile.o: src/tile.cpp include/Tile.h include/Vec2f.h
	g++ -c src/tile.cpp -o obj/tile.o -I include -I library -Wall

obj/vec2f.o: src/vec2f.cpp include/Vec2f.h
	g++ -c src/vec2f.cpp -o obj/vec2f.o -I include -I library -Wall

obj/winTxt.o: src/winTxt.cpp library/winTxt.h
	g++ -c src/winTxt.cpp -o obj/winTxt.o -I include -I library -Wall

clean:
	rm obj/*.o bin/*.exe