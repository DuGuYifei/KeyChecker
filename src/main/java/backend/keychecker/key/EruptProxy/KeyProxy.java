package backend.keychecker.key.EruptProxy;

import backend.keychecker.digest.Sha256;
import backend.keychecker.key.entity.Key;
import org.springframework.stereotype.Service;
import xyz.erupt.annotation.fun.DataProxy;

import java.sql.Timestamp;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.UUID;

@Service
public class KeyProxy implements DataProxy<Key> {
    @Override
    public void beforeAdd(Key key) {
        String keyStr = Sha256.hash(UUID.randomUUID().toString());
        Date date = new Date();
        Calendar calendar = new GregorianCalendar();
        calendar.setTime(date);
        calendar.add(Calendar.DATE, 30);
        Timestamp timestamp = new Timestamp(calendar.getTime().getTime());
        key.setKeyStr(keyStr);
        key.setExpire(timestamp);
        key.setMacHash(null);
    }
}
