package backend.keychecker.key.dto;


import backend.keychecker.key.entity.Key;
import lombok.*;

import java.sql.Timestamp;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.function.BiFunction;

@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
public class UpdateRenewExpireAndUserRequest {

    private int dayCount;

    private String user;

    public static BiFunction<Key, UpdateRenewExpireAndUserRequest, Key> dtoToEntityUpdater() {

        return (key, request) -> {
            Date date = new Date();
            Calendar calendar = new GregorianCalendar();
            calendar.setTime(date);
            calendar.add(Calendar.DATE, request.getDayCount());
            Timestamp timestamp = new Timestamp(calendar.getTime().getTime());
            key.setExpire(timestamp);
            key.setUser(request.getUser());
            return key;
        };
    }

}
