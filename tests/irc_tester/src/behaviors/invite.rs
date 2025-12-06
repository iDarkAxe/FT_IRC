use crate::client::Client;
use anyhow::Result;

//Rpl inviting

pub async fn invite_need_more_params(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("inv_needmore_p_{}", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;
    client
        .send(
            &format!(
                "USER {}_invite_more_params 0 * :invite_need_more_params\r\n",
                nick
            ),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }

    client.send("INVITE \r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :Not enough parameters") {
            return Err(anyhow::anyhow!("Err_NEEDMOREPARAMS missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn invite_not_on_channel(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("inv_notonchan_{}", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;
    client
        .send(
            &format!(
                "USER {}_invite_more_params 0 * :invite_need_more_params\r\n",
                nick
            ),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("Welcome message missing | received [{line}]"));
        }
    }

    client.send("INVITE reserved_nick #channel\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :You're not on that channel") {
            return Err(anyhow::anyhow!("ERR_NOTONCHANNEL missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn invite_no_such_nick(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("invnosuch_n_{}", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;
    client
        .send(
            &format!(
                "USER {}_invite_more_params 0 * :invite_need_more_params\r\n",
                nick
            ),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }
    client.send("JOIN #join_no_such_nick_test\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("JOIN #join_no_such_nick_test") {
            return Err(anyhow::anyhow!("Failed to join a valid chan | received [{line}]"));
        }
    }
    client.send("INVITE nosuchnickname #join_no_such_nick_test\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :No such nick/channel") {
            return Err(anyhow::anyhow!("Err_NOSUCHNICK missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())
}

pub async fn invite_no_priv(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("{}_invite_no_priv", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;
    client
        .send(
            &format!(
                "USER {}_invite_more_params 0 * :invite_need_more_params\r\n",
                nick
            ),
            0,
        )
        .await?;

    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("Welcome to the Internet Relay Network") {
            return Err(anyhow::anyhow!("welcome message missing | received [{line}]"));
        }
    }
    client.send("JOIN #join_no_priv\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains("JOIN #join_no_priv") {
            return Err(anyhow::anyhow!("Failed to join a valid chan | received [{line}]"));
        }
    }
    client.send("INVITE reserved_nick #join_no_priv\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :You're not channel operator") {
            return Err(anyhow::anyhow!("ERR_CHANOPRIVSNEED missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())

}

pub async fn invite_not_registered(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("{}_not_registered", id);
    let mut client = Client::connect(port).await?;

    client.send("PASS password\r\n", 0).await?;
    client
        .send(&format!("NICK {}\r\n", nick), 0)
        .await?;

    client.send("INVITE reserved_nick #join_no_priv\r\n", 0).await?;
    if let Some(line) = client.read_line_timeout(timeout_ms).await? {
        if !line.contains(" :You have not registered") {
            return Err(anyhow::anyhow!("ERR_NOTREGISTERED missing | received [{line}]"));
        }
    }
    client.shutdown().await?;
    Ok(())

}
