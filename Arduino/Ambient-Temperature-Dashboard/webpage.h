#ifndef WEBPAGE_H
#define WEBPAGE_H

const char webpage[] = R"====(
  <!DOCTYPE html>
  <html>

  <head>
    <title>Ambient Temperature Sensor</title>

    <meta name="viewport" content="width=device-width, initial-scale=1">

    <style>

      body{
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
        text-align: center;
        height: 100vh;
        overflow: hidden;
      }

      h1{
        font-size: 4rem;
      }

      .info{
        display: flex;
        flex-direction: row;
        
        align-items: center;
        /* background-color: red; */
        width: 75%;
        height: 50vh;
        padding: 10px;
        /* border: 5px solid black; */
        border-radius: 30px;
      }

      .main{
        display: flex;
        justify-content: center;
        align-items: center;
        width: 100%;
        height: 50%;
      }

      .details{
        display: flex;
        flex-wrap: wrap;
        flex-direction: row;
        justify-content: space-around;
        align-items: center;
        height: min-content;
        width: 100%;
      }

      .block{
        padding: 20px 40px 40px;
        display: flex;
        justify-content: center;
        align-items: center;
        text-align: left;
        background-color: white;
        border-radius: 15px;
        border-bottom: 10px solid green;
        box-shadow: 0px 0px 10px 5px rgba(0, 0, 0, 0.2);
        width: 20%;
        height: 100px;

        transition: border-bottom-color 0.3s ease;
      }
    
    </style>

    <script>

      function updateSensor(){

        fetch('/sensor')
        .then(response => response.json())
        .then(data => {

          document.getElementById("temp").innerHTML =
          data.temperature + "&deg;C";

          document.getElementById("hum").innerHTML =
          "Humidity: " + data.humidity + " %";

          document.getElementById("fah").innerHTML =
          data.fahrenheit + "&deg;F";

          let temp = data.temperature;
          let hum = data.humidity;
          let fahrenheit = data.fahrenheit;
          let block = document.getElementById("tempBlock");

          if(temp <= 23){
            block.style.borderBottomColor = "blue";
          } else if(temp > 23 && temp < 30){
            block.style.borderBottomColor = "green";
          } else {
            block.style.borderBottomColor = "red";
          }

        });

      }

      updateSensor();

      // update every 2 seconds
      setInterval(updateSensor, 2000);

    </script>

  </head>

  <body>

    <h1>Room Temperature Dashboard</h1>

    <div class="info">

      

      <div class="details">

        <div class="block" id="tempBlock">
          <h2 id="temp">%TemperatureC% &deg;C</h2>
        </div>

        <div class="block" id="tempfBlock">
          <h2 id="fah">%TemperatureF% &deg;F</h2>
        </div>

        <div class="block" id="humBlock">
          <h2 id="hum">Humidity: %Humidity%%</h2>
        </div>

      </div>

      
    </div>

  </body>
  
</html>



)====";

#endif
