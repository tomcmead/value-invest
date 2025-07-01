# Value Invest Pricing Algorithm
The Value Invest algorithm determines a stock's intrinsic value by analysing historical data. It leverages real-time market data sourced via the Alpha Vantage API, with cURL and RapidJSON for request handling. The algorithm then computationally derives the intrinsic value from this processed data. Logging is managed by spdlog and rigorous testing is achieved using GTest. Docker simplifies the build process.

## Technologies
* **Google Test (GTest)**
* **cURL**
* **RapidJSON**
* **spdlog**
* **Alpha Vantage API**
* **Docker**

## How to Run
1. Install and run Docker: https://docs.docker.com/engine/install/
2. Generate Alpha Advantage API Key: https://www.alphavantage.co/support/#api-key
3. git pull https://github.com/tomcmead/value-invest.git
4. cd ./value-invest
5. docker build -t value-invest-image .
6. docker run -e ALPHA_VANTAGE_API_KEY=[***ALPHA_VANTAGE_API_KEY***] value-invest-image