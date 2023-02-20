package backend.keychecker.key.dto;


import backend.keychecker.digest.Sha256;
import backend.keychecker.key.entity.Key;
import lombok.*;

import java.sql.Timestamp;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.UUID;
import java.util.function.Function;

@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor(access = AccessLevel.PRIVATE)
@ToString
@EqualsAndHashCode
public class CreateKeyRequest {

    private String user;

    public static Function<CreateKeyRequest, Key> dtoToEntityMapper(){
        String keyStr = Sha256.hash(UUID.randomUUID().toString());
        Date date = new Date();
        Calendar calendar = new GregorianCalendar();
        calendar.setTime(date);
        calendar.add(Calendar.DATE, 30);
        Timestamp timestamp = new Timestamp(calendar.getTime().getTime());
        return request -> Key.builder()
                .keyStr(keyStr)
                .user(request.getUser())
                .expire(timestamp)
                .macHash(null)
                .build();
    }

}
