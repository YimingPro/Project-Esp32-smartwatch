package sample;

import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonParser;


import java.util.HashMap;

public class JsonHttpParser {

    public HashMap<String, Integer> parseHeartRate(String messg) {

        HashMap<String, Integer> heartRateData = new HashMap<String, Integer>();
        try {

            JsonParser jsonParser = new JsonParser();

            JsonArray jsonArray = jsonParser.parse(messg).getAsJsonArray();

            for (JsonElement object: jsonArray) {

                System.out.println("timestamp:"
                        +object.getAsJsonObject().get("created_at").toString()
                        +"\tvalue:"+
                        object.getAsJsonObject().get("value").toString() );
                
                heartRateData.put(object.getAsJsonObject().get("created_at").toString(),object.getAsJsonObject().get("value").getAsInt());

            }

        } catch (Exception e) {
            e.printStackTrace();
        }

        return heartRateData;
    }
}
