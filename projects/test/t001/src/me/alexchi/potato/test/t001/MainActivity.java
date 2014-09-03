package me.alexchi.potato.test.t001;

//import me.alexchi.test.R;
import me.alexchi.potato.PActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends PActivity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		Log.d("MainActivity", "onCreate");
	}

}
