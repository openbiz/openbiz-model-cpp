package com.openbiz.lib;

import android.content.Context;

public class OpenbizHelper {
	
	private static Context sContext = null;
	private static String sFileDirectory;
	
	public static <T> void init(T pContext) {
		if(pContext instanceof Context){
			Context context = (Context )pContext;
			OpenbizHelper.sContext = context;
			OpenbizHelper.sFileDirectory = context.getFilesDir().getAbsolutePath();
		}
	}
	
	public static String getWritablePath() {
		return OpenbizHelper.sFileDirectory;
	}
}
