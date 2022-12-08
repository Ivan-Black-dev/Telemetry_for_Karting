import folium

path = input('Ввиедите путь к файлу: ')

with open('DATALOG.TXT', 'r') as f:
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




Map = folium.Map(location = [55.9009361267,37.3952522277],    # широта и долгота России
    zoom_start = 20)

coordinates = []
for dot in dots:
    coordinates.append(dot['coordinat'])
    folium.Marker(dot['coordinat'],
                  tooltip=dot['speed'],
                  popup=f"{dot['time']}\n{dot['temp']}C\n{dot['hum']}%"
                  ).add_to(Map)


folium.PolyLine(coordinates,
                color='red',
                weight=5,
                opacity=0.8).add_to(Map)

Map.save('map.html')


