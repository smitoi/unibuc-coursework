package services.database;

import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class CSVLogger {
    private static CSVLogger csvLogger = null;
    FileWriter logWriter = null;

    private CSVLogger() throws IOException {
        logWriter = new FileWriter(String.format("./src/services/database/csv/%s-log.txt", this.getTimestamp()));
        System.out.println(String.format("./src/services/database/csv/%s-log.txt", this.getTimestamp()));
    }

    public FileWriter getLogWriter() {
        return logWriter;
    }

    public static CSVLogger getInstance() throws IOException {
        if (csvLogger == null)
            csvLogger = new CSVLogger();

        return csvLogger;
    }

    public String getTimestamp() {
        return new SimpleDateFormat("yyyy-MM-dd-HH-mm-ss").format(new Date());
    }

    public void writeAction(String action) throws IOException {
        logWriter.write(String.format("%s %s\n", action, this.getTimestamp()));
    }
}
