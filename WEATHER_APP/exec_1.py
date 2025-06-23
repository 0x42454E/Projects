from flask import render_template, Flask, request
import requests
import datetime
from geopy.geocoders import Nominatim


app = Flask(__name__)

#OpenWeather API key
API_KEY = '2804fe592b69627b744cd6626a346344'

#Route establishment
@app.route('/')
def input_city():
    return render_template('index.html')

@app.route('/weather', methods=['POST', 'GET'])
def weather():
        city = request.form['city']
        geolocator = Nominatim(user_agent = 'MyApp')
        country = geolocator.geocode(f'{city}')


        #Current weather API call
        forecast_url = f'http://api.openweathermap.org/data/2.5/forecast?q={city}&appid={API_KEY}&units=metric'
        forecast_response = requests.get(forecast_url)
        forecast_data = forecast_response.json()

        weekly_forecast = []
        if forecast_data['cod'] == '200':
            current_date = None
            forecast_group = None
            for forecast in forecast_data['list']:
                forecast_date = datetime.datetime.fromtimestamp(forecast['dt']).strftime('%Y-%m-%d')
                forecast_day = datetime.datetime.fromtimestamp(forecast['dt']).strftime('%A')
                if forecast_date != current_date:
                    if forecast_group:
                        weekly_forecast.append(forecast_group)
                    forecast_group = {
                        'country' : country,
                        'location' : city,
                        'day': forecast_day,
                        'date': forecast_date,
                        'temperature': forecast['main']['temp'],
                        'humidity': forecast['main']['humidity'],
                        'wind_speed': forecast['wind']['speed'],
                        'description': forecast['weather'][0]['description'],
                        'forecasts': []
                    }
                    current_date = forecast_date
                forecast_item = {
                    'temperature' : forecast['main']['temp'],
                    'description' : forecast['weather'][0]['description']
                }
                forecast_group['forecasts'].append(forecast_item)
            if forecast_group:
                weekly_forecast.append(forecast_group)

        else:
            error_message = forecast_data['message']
            return render_template('error.html', error_message=error_message)

        return render_template('/weather.html',weekly_forecast=weekly_forecast)

if __name__ == '__main__':
    app.run(debug=True)

