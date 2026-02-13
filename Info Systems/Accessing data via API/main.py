import tkinter as tk
import requests
import geocoder

def get_sun_time():
    city = city_ent.get()
    try:
        geo = geocoder.arcgis(city)
        lat = geo.json['lat']
        lng = geo.json['lng']
        url = 'https://api.sunrise-sunset.org/json'
        params = {'lat': lat, 'lng': lng, 'date':"2026-02-09"}
        response = requests.get(url, params=params)
        data = response.json()
        sunrise.config(text=f"Рассвет: {data['results']['sunrise']}")
        sunset.config(text=f"Закат: {data['results']['sunset']}")
    except:
        sunrise.config(text="Ошибка")
        sunset.config(text="Введите реальный город")

root = tk.Tk()
root.title("Время рассвета и заката")
root.geometry("300x300")

tk.Label(root, text="Введите город:").pack()

city_ent = tk.Entry(root, width=25)
city_ent.pack()

tk.Button(root, text="Показать время", command=get_sun_time).pack()

sunrise = tk.Label(root, text="Рассвет: ")
sunrise.pack()

sunset = tk.Label(root, text="Закат: ")
sunset.pack()

root.mainloop()