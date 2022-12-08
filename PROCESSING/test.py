import folium

#path = input('Ввиедите путь к файлу')

with open('DATALOG.TXT', 'r') as f:
    g = [ i for i in f.read().split('\n')]


cor = []
time = []
speed = []
for i in g:
    data = i.split(',')
    k = tuple(data[0].split(' '))
    cor.append(k)

res = []
for i in cor[:-1]:
    res.append((float(i[0]), float(i[1])))
print(res)


m = folium.Map(location = [55.9009361267,37.3952522277],    # широта и долгота России
    zoom_start = 20)



folium.PolyLine(res,
                color='red',
                weight=200,
                opacity=0.8).add_to(m)
m.save('map.html')

