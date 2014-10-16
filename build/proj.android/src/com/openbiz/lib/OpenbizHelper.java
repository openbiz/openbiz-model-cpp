package com.openbiz.lib;

import android.content.Context;

public class OpenbizHelper {
	
	private static Context sContext = null;
	private static String sFileDirectory;
	
	public static void init(final Context pContext) {
		OpenbizHelper.sContext = pContext;
		OpenbizHelper.sFileDirectory = pContext.getFilesDir().getAbsolutePath();
	}
	
	public static String getWritablePath() {
		return OpenbizHelper.sFileDirectory;
	}
}
