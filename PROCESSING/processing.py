import folium

path = input('Ввиедите путь к файлу: ')

with open(path, 'r') as f:
    g = [ i for i in f.read().split('\n')]


dots = []
for line in g[:-1]:
    data = line.split(' ')
    dot = {
        'coordinat': (float(data[1]), float(data[2])),
        'time': data[3],
        'speed': float(data[4]),
        'temp': float(data[5]),
        'hum': float(data[6])
        }
    dots.append(dot)

Speed = []
Temp = []
Hum = []

for dot in dots:
    Speed.append(dot['speed'])
    Temp.append(dot['temp'])
    Hum.append(dot['hum'])

avgSpeed = sum(Speed)/len(Speed)
avgTemp = sum(Temp)/len(Temp)
avgHum = sum(Hum)/len(Hum)

data = f'<h3 align="center" style="font-size:16px"><b>Средняя скорость: {round(avgSpeed, 2)}км/ч.</br> Средняя температура: {round(avgTemp, 2)}℃</br>Средняя влажность: {round(avgHum, 2)}%</b></h3>'


Map = folium.Map(location = [55.9009361267,37.3952522277],    # широта и долгота России
    zoom_start = 20)



coordinates = []
for dot in dots:
    coordinates.append(dot['coordinat'])
    '''
    folium.Marker(dot['coordinat'],
                  tooltip=dot['speed'],
                  popup=f"{dot['time']}\n{dot['temp']}C\n{dot['hum']}%"
                  ).add_to(Map)'''


folium.PolyLine(coordinates,
                color='red',
                weight=5,
                tooltip=str(int(dot['speed'])) + ' км/ч' ,
                popup=f"{dot['time']}\n{dot['temp']}C\n{dot['hum']}%",
                opacity=0.8).add_to(Map)

Map.get_root().html.add_child(folium.Element(data))



Map.save('map.html')


