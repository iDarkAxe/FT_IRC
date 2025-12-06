use crate::client::Client;
use anyhow::Result;

pub async fn nick_normal_claim_and_change(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("nick_change_{}", id);
    let mut client = Client::connect(port).await?;
    client.authenticate(nick, timeout_ms).await?;
    client.try_expect("NICK {}_claimed\r\n", "updated his nickname to", "Failed to update nickname ", timeout_ms).await?;
    client.shutdown().await?;
    Ok(())
}

pub async fn nick_no_nickname_given(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("nonickgiven_{}", id);
    let mut client = Client::connect(port).await?;
    client.authenticate(nick, timeout_ms).await?;
    client.try_expect("NICK\r\n", "No nickname given", "Failed to reject update ", timeout_ms).await?;
    client.shutdown().await?;
    Ok(())
}

pub async fn nick_already_in_use(port: u16, _id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("reserved_nick");
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;
    client
        .send(&format!("USER {} 0 * :nickalreadyinuse\r\n", nick), 0)
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :Nickname is already in use") {
            return Err(anyhow::anyhow!("ERR_NICKALREADYINUSE missing | received [{line}]"));
        }
    }

    client.shutdown().await?;
    Ok(())
}


