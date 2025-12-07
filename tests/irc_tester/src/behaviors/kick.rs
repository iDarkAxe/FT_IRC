use crate::client::Client;
use anyhow::Result;

// ClientBehavior::KickBadChanMask,
// ClientBehavior::KickChaNoPrivsNeeded,
// ClientBehavior::KickUserNotInChannel,

pub async fn kick_not_registered(port: u16, _id: usize, timeout_ms: u64) -> Result<()> {
    let mut client = Client::connect(port).await?;
    client.send("PASS password\r\n", 0).await?;
    client
        .try_expect(
            "KICK\r\n",
            " :You have not registered",
            "ERR_NOTREGISTERED missing",
            timeout_ms,
        )
        .await?;
    client.shutdown().await?;
    Ok(())
}

pub async fn kick_need_more_params(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("kickneedmorep_{}", id);
    let mut client = Client::connect(port).await?;

    client.authenticate(nick, timeout_ms).await?;
    client
        .try_expect(
            "KICK \r\n",
            " :Not enough parameters",
            "ERR_NEEDMOREPARAMS missing ",
            timeout_ms,
        )
        .await?;
    client.shutdown().await?;
    Ok(())
}

pub async fn kick_no_such_channel(port: u16, id: usize, timeout_ms: u64) -> Result<()> {
    let nick = format!("Kick_no_such_chan_{}", id);
    let mut client = Client::connect(port).await?;

    client.authenticate(nick, timeout_ms).await?;
    client
        .try_expect(
            "KICK #nosuchchannel user\r\n",
            " :No such channel",
            "ERR_NOSUCHCHAN missing ",
            timeout_ms,
        )
        .await?;
    client.shutdown().await?;
    Ok(())
}
