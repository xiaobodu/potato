package me.alexchi.potato.test.t001;

//import me.alexchi.test.R;
import me.alexchi.potato.PActivity;
import me.alexchi.test.R;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends PActivity {

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.main);

		Button btn = (Button) findViewById(R.id.button1);
		btn.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				toDebug();
			}
		});
	}

}
