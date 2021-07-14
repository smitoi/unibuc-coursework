package app;

import state.AppState;

import java.io.IOException;

public class App {
    public static void main(String[] args) throws IOException {
        AppState appState = new AppState();
        appState.execute();
    }
}