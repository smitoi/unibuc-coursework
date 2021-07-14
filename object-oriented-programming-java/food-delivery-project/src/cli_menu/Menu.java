package cli_menu;

import state.AppState;

import java.io.IOException;

public abstract class Menu {
    public AppState currentState;

    public abstract void handleMenu() throws IOException;
}
