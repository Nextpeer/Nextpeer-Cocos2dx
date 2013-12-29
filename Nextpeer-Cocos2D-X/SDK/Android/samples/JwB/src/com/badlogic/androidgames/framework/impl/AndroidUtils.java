package com.badlogic.androidgames.framework.impl;

import android.os.Build;

/* package */ class AndroidUtils {

    /* package */ static final int CURRENT_API_LEVEL = AndroidUtils.getApiLevel();
    
    /**
     * @return current Android API level.
     */
    private static int getApiLevel()
    {
        try
        {
            // Although the Build.VERSION.SDK field has existed since API 1, it is deprecated and could be removed
            // in the future. Therefore use reflection to retrieve it for maximum forward compatibility.
            final Class<?> buildClass = Build.VERSION.class;
            final String sdkString = (String) buildClass.getField("SDK").get(null);
            return Integer.parseInt(sdkString);
        }
        catch (final Exception e)
        {
            // Although probably not necessary, protects from the aforementioned deprecation
            try
            {
                final Class<?> buildClass = Build.VERSION.class;
                return buildClass.getField("SDK_INT").getInt(null);
            }
            catch (final Exception ignore)
            {
            }
        }

        // Worse-case scenario, assume Cupcake
        return 3;
    }
}
